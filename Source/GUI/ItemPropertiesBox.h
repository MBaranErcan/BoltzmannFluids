#ifndef ITEMPROPERTIESBOX_H
#define ITEMPROPERTIESBOX_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include "AddItemsBox.h"

class QGroupBox;

class ItemPropertiesBox : public QWidget
{
    Q_OBJECT

public:

    explicit ItemPropertiesBox(QWidget* parent = nullptr);


private:
    AddableItem* item;
    QLabel* name_label;
    QLabel* type_label;
    QDoubleSpinBox* position_X_box;
    QDoubleSpinBox* position_Y_box;
    QDoubleSpinBox* position_Z_box;
    QDoubleSpinBox* size_X_box;
    QDoubleSpinBox* size_Y_box;
    QDoubleSpinBox* size_Z_box;

    QGroupBox* createInitialConditionsGroup();

    bool is_item_selected = false;

    void update_styles();
    void update_property_fields();

public slots:
    void set_selected_item(AddableItem& new_item);
    void reset_selected_item();

};



#endif // ITEMPROPERTIESBOX_H
