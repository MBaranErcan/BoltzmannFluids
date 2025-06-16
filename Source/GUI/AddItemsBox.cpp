#include "AddItemsBox.h"

#include <QVBoxLayout>

AddableItem::AddableItem(QString name, Type type, QIcon icon, QVector3D pos, QVector3D size)
    : name(std::move(name)), type(type), icon(std::move(icon)), pos(pos), size(size)
{
}

AddableItemModel::AddableItemModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int AddableItemModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(_items.size());
}

QVariant AddableItemModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= static_cast<int>(_items.size()))
        return {};

    const AddableItem& item = _items[index.row()];

    if (role == Qt::DisplayRole)
        return item.name;
    else if (role == Qt::DecorationRole)
        return item.icon;

    return {};
}

void AddableItemModel::set_items(const std::vector<AddableItem>& items) {
    beginResetModel();
    _items = items;
    endResetModel();
}

const AddableItem& AddableItemModel::item_at(int index) const {
    return _items[index];
}


AddItemsBox::AddItemsBox(QWidget *parent)
    :QWidget(parent)
{
    auto main_layout = new QVBoxLayout(this);
    setLayout(main_layout);

    _model = new AddableItemModel(this);
    _items_list = new QListView(this);
    _items_list->setSelectionMode(QAbstractItemView::SingleSelection);
    main_layout->addWidget(_items_list);

    {
        auto button_layout = new QHBoxLayout;
        main_layout->addLayout(button_layout);

        _add_button = new QPushButton("Add", this);
        button_layout->addWidget(_add_button);

        _delete_button = new QPushButton("Delete", this);
        button_layout->addWidget(_delete_button);
    }


    connect(_add_button, &QPushButton::clicked, this, [this]() {
        QModelIndex index = _items_list->currentIndex();
        if (index.isValid())
            emit add_item_request(_model->item_at(index.row()));
    });

    connect(_delete_button, &QPushButton::clicked, this, [this]() {
        QModelIndex index = _items_list->currentIndex();
        if (index.isValid())
            emit delete_item_request(_model->item_at(index.row()));
    });

    connect(_items_list->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        bool has_selection = _items_list->currentIndex().isValid();
        _add_button->setEnabled(has_selection);
        _delete_button->setEnabled(has_selection);

        if (has_selection) {
            const auto& item = _model->item_at(_items_list->currentIndex().row());
            emit item_selected(item);  // new signal
        } else {
            emit item_deselected();
        }
    });


    // Default items
    std::vector<AddableItem> items;

    items.emplace_back("Cube", Type::CUBE, QIcon(":/icons/cube_icon.png"));
    items.emplace_back("Sphere", Type::SPHERE, QIcon(":/icons/sphere_icon.png"));
    items.emplace_back("Cylinder", Type::CYLINDER, QIcon(":/icons/cylinder_icon.png"));

    _model->set_items(items);
    _items_list->setModel(_model);
}
