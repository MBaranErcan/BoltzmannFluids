#include "ItemPropertiesBox.h"
#include "UI_Config.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <qlineedit.h>

ItemPropertiesBox::ItemPropertiesBox(QWidget *parent)
    :QWidget(parent)
{
    auto main_layout = new QVBoxLayout(this);
    main_layout->setAlignment(Qt::AlignTop);
    main_layout->addWidget(createInitialConditionsGroup());
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(0);
    setLayout(main_layout);

    item = nullptr;
//    setStyleSheet();

}

void ItemPropertiesBox::set_selected_item(AddableItem& new_item)
{
    this->item = &new_item;
    is_item_selected = true;
    update_property_fields();
    update_styles();
}

void ItemPropertiesBox::reset_selected_item()
{
    is_item_selected = false;
    update_property_fields();
    update_styles();
}

void ItemPropertiesBox::update_styles()
{
    if (is_item_selected) {
        setStyleSheet("QWidget { background-color: rgb(70, 80, 90); border: 2px solid #88f; }");
    } else {
        setStyleSheet("QWidget { background-color: rgb(50, 50, 50); border: 1px dashed #444; }");
    }
}

void ItemPropertiesBox::update_property_fields()
{
    if (!item) {
        qDebug() << "(ItemPropertiesBox::update_property_fields) \"item\" is nullptr";
        return;
    }

    name->setText(item->name);
    type = &(item->type);

    pos_x->setValue(item->pos.x());
    pos_y->setValue(item->pos.y());
    pos_z->setValue(item->pos.z());

    size_x->setValue(item->size.x());
    size_y->setValue(item->size.y());
    size_z->setValue(item->size.z());
}


QGroupBox *ItemPropertiesBox::createInitialConditionsGroup()
{
    auto group = new QGroupBox(this);

    auto layout = new QVBoxLayout(group);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    group->setLayout(layout);

    /**/
    {   // Name & Type
        auto name_vertical = new QVBoxLayout();
        name_vertical->setContentsMargins(0, 0, 0, 0);
        name_vertical->setSpacing(0);
        layout->addLayout(name_vertical);

        auto name_label = new QLabel("BoltzmannFluids"); // Can this be default name at the beginning.
        name_vertical->addWidget(name_label);

        auto type_label = new QLabel("Object"); // This is default too.
        name_vertical->addWidget(type_label);
    }

    //// Position
    {
        auto position_vertical = new QVBoxLayout();
        position_vertical->setContentsMargins(0, 0, 0, 0);
        position_vertical->setSpacing(0);
        layout->addLayout(position_vertical);

        // Label
        auto position_label = new QLabel("Position");
        position_vertical->addWidget(position_label);

        auto position_horizontal = new QHBoxLayout();
        position_horizontal->addStretch();

        /// X
        auto position_X_txt = new QLabel("X:");
        position_horizontal->addWidget(position_X_txt);
        auto position_X_box = new QDoubleSpinBox();
        position_X_box->setRange(POSITION_MIN, POSITION_MAX);
        position_X_box->setSingleStep(0.01);
        position_horizontal->addWidget(position_X_box);
        /// Y
        auto position_Y_txt = new QLabel("y:");
        position_horizontal->addWidget(position_Y_txt);
        auto position_Y_box = new QDoubleSpinBox();
        position_Y_box->setRange(POSITION_MIN, POSITION_MAX);
        position_Y_box->setSingleStep(0.01);
        position_horizontal->addWidget(position_Y_box);
        /// Z
        auto position_Z_txt = new QLabel("z:");
        position_horizontal->addWidget(position_Z_txt);
        auto position_Z_box = new QDoubleSpinBox();
        position_Z_box->setRange(POSITION_MIN, POSITION_MAX);
        position_Z_box->setSingleStep(0.01);
        position_horizontal->addWidget(position_Z_box);

        position_vertical->addLayout(position_horizontal);
    }
    /**/

    return group;
}
