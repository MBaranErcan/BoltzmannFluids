#include "ItemPropertiesBox.h"
#include "UI_Config.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <cfloat>
#include <qlineedit.h>

void enum_to_qstring(Type& type, QLabel* _string) ;

ItemPropertiesBox::ItemPropertiesBox(QWidget *parent)
    :QWidget(parent)
{
    auto main_layout = new QVBoxLayout(this);
    main_layout->setAlignment(Qt::AlignTop);
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(9);
    setLayout(main_layout);

    QString item_properties_qss;

    /// Initialize AddableItem "item"
    item = new AddableItem(QString("Object"), Type::CUBE, QIcon());

    {   /// Name & Type
        auto name_vertical = new QVBoxLayout();
        name_vertical->setContentsMargins(0, 0, 0, 0);
        name_vertical->setSpacing(0);
        main_layout->addLayout(name_vertical);

        name_label = new QLabel("BoltzmannFluids");
        name_vertical->addWidget(name_label);

        type_label = new QLabel("Object");
        name_vertical->addWidget(type_label);
    }

    /// Position
    {
        auto position_vertical = new QVBoxLayout();
        position_vertical->setContentsMargins(0, 0, 0, 0);
        position_vertical->setSpacing(0);
        main_layout->addLayout(position_vertical);

        // Label
        auto position_label = new QLabel("Position");
        position_vertical->addWidget(position_label);

        auto position_horizontal = new QHBoxLayout();
        position_horizontal->addStretch();

        /// X
        auto position_X_txt = new QLabel("X:");
        position_horizontal->addWidget(position_X_txt);
        position_X_box = new QDoubleSpinBox();
        position_X_box->setMinimumWidth(50);
        position_X_box->setDecimals(DECIMAL_COUNT);
        position_X_box->setRange(POSITION_MIN, POSITION_MAX);
        position_X_box->setSingleStep(0.01);
        position_horizontal->addWidget(position_X_box);
        /// Y
        auto position_Y_txt = new QLabel("Y:");
        position_horizontal->addWidget(position_Y_txt);
        position_Y_box = new QDoubleSpinBox();
        position_Y_box->setMinimumWidth(50);
        position_Y_box->setDecimals(DECIMAL_COUNT);
        position_Y_box->setRange(POSITION_MIN, POSITION_MAX);
        position_Y_box->setSingleStep(0.01);
        position_horizontal->addWidget(position_Y_box);
        /// Z
        auto position_Z_txt = new QLabel("Z:");
        position_horizontal->addWidget(position_Z_txt);
        position_Z_box = new QDoubleSpinBox();
        position_Z_box->setMinimumWidth(50);
        position_Z_box->setDecimals(DECIMAL_COUNT);
        position_Z_box->setRange(POSITION_MIN, POSITION_MAX);
        position_Z_box->setSingleStep(0.01);
        position_horizontal->addWidget(position_Z_box);

        position_vertical->addLayout(position_horizontal);
    }

    /// Size
    {
        auto size_vertical = new QVBoxLayout();
        size_vertical->setContentsMargins(0, 0, 0, 0);
        size_vertical->setSpacing(0);
        main_layout->addLayout(size_vertical);

        // Label
        auto size_label = new QLabel("Size");
        size_vertical->addWidget(size_label);

        auto size_horizontal = new QHBoxLayout();
        size_horizontal->addStretch();

        /// X
        size_horizontal->addStretch();
        auto size_X_txt = new QLabel("X:");
        size_horizontal->addWidget(size_X_txt);
        size_X_box = new QDoubleSpinBox();
        size_X_box->setMinimumWidth(50);
        size_X_box->setDecimals(DECIMAL_COUNT);
        size_X_box->setRange(POSITION_MIN, POSITION_MAX);
        size_X_box->setSingleStep(0.01);
        size_horizontal->addWidget(size_X_box);
        /// Y
        auto size_Y_txt = new QLabel("y:");
        size_horizontal->addWidget(size_Y_txt);
        size_Y_box = new QDoubleSpinBox();
        size_Y_box->setMinimumWidth(50);
        size_Y_box->setDecimals(DECIMAL_COUNT);
        size_Y_box->setRange(POSITION_MIN, POSITION_MAX);
        size_Y_box->setSingleStep(0.01);
        size_horizontal->addWidget(size_Y_box);
        /// Z
        auto size_Z_txt = new QLabel("z:");
        size_horizontal->addWidget(size_Z_txt);
        size_Z_box = new QDoubleSpinBox();
        size_Z_box->setMinimumWidth(50);
        size_Z_box->setDecimals(DECIMAL_COUNT);
        size_Z_box->setRange(POSITION_MIN, POSITION_MAX);
        size_Z_box->setSingleStep(0.01);
        size_horizontal->addWidget(size_Z_box);

        size_vertical->addLayout(size_horizontal);
    }

    main_layout->update();

    update_styles();
    //setStyleSheet(item_properties_qss);
}

void ItemPropertiesBox::set_selected_item(AddableItem& new_item)
{
    qDebug() << "[ItemPropertiesBox] set_selected_item called for" << new_item.name;

    item = &new_item;
    is_item_selected = true;
    update_property_fields();
    update_styles();
}

void ItemPropertiesBox::reset_selected_item()
{
    qDebug() << "[ItemPropertiesBox] reset_selected_item called";

    is_item_selected = false;
    update_property_fields();
    update_styles();
}

void ItemPropertiesBox::update_styles()
{
    if (is_item_selected) {
        setStyleSheet(
            "ItemPropertiesBox QWidget {"
                "color: rgb(225, 226, 227);"
            "}"
            "ItemPropertiesBox QDoubleSpinBox {"
                "color: rgb(225, 226, 227);"
                "border: 1px solid rgb(80, 81, 82);"
                "background-color: rgb(85, 86, 87);"
            "}"
            "ItemPropertiesBox QDoubleSpinBox:hover {"
                "background-color: rgb(110, 111, 112);"
            "}"
            );
        position_X_box->setEnabled(true);
        position_Y_box->setEnabled(true);
        position_Z_box->setEnabled(true);
        size_X_box->setEnabled(true);
        size_Y_box->setEnabled(true);
        size_Z_box->setEnabled(true);
    }
    else {
        setStyleSheet(
            "ItemPropertiesBox QDoubleSpinBox {"
                "color: rgb(165, 166, 167);"
                "border: 1px solid rgb(60, 61, 62);"
                "background-color: rgb(65, 66, 67);"
            "}"
            "ItemPropertiesBox QDoubleSpinBox:hover {"
                "background-color: rgb(110, 111, 112);"
            "}"
            );
        position_X_box->setEnabled(false);
        position_Y_box->setEnabled(false);
        position_Z_box->setEnabled(false);
        size_X_box->setEnabled(false);
        size_Y_box->setEnabled(false);
        size_Z_box->setEnabled(false);

    }
}

void ItemPropertiesBox::update_property_fields()
{
    if (!item) {
        qDebug() << "(ItemPropertiesBox::update_property_fields) \"item\" is nullptr";
        return;
    }


    name_label->setText(item->name);
    enum_to_qstring(item->type, type_label);

    position_X_box->setValue(item->pos.x());
    position_Y_box->setValue(item->pos.y());
    position_Z_box->setValue(item->pos.z());

    size_X_box->setValue(item->size.x());
    size_Y_box->setValue(item->size.y());
    size_Z_box->setValue(item->size.z());
}


void enum_to_qstring(Type& type, QLabel* _string) {
    switch (type) {
    case Type::CUBE:
        _string->setText("Cube");
        break;
    case Type::SPHERE:
        _string->setText("Sphere");
        break;
    case Type::CYLINDER:
        _string->setText("Cylinder");
        break;
    }
}
