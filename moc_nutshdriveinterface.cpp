/****************************************************************************
** Meta object code from reading C++ file 'nutshdriveinterface.h'
**
** Created: Sun Apr 5 19:43:24 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nutshdriveinterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nutshdriveinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NutshDriveInterface[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      44,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NutshDriveInterface[] = {
    "NutshDriveInterface\0\0changeDir(QModelIndex)\0"
    "precedent()\0"
};

const QMetaObject NutshDriveInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NutshDriveInterface,
      qt_meta_data_NutshDriveInterface, 0 }
};

const QMetaObject *NutshDriveInterface::metaObject() const
{
    return &staticMetaObject;
}

void *NutshDriveInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NutshDriveInterface))
        return static_cast<void*>(const_cast< NutshDriveInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int NutshDriveInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeDir((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: precedent(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
