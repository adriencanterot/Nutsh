/****************************************************************************
** Meta object code from reading C++ file 'nutshsearchlineinterface.h'
**
** Created: Sun Apr 12 21:47:03 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nutshsearchlineinterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nutshsearchlineinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NutshSearchLineInterface[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NutshSearchLineInterface[] = {
    "NutshSearchLineInterface\0\0"
    "showResults(QString)\0"
};

const QMetaObject NutshSearchLineInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NutshSearchLineInterface,
      qt_meta_data_NutshSearchLineInterface, 0 }
};

const QMetaObject *NutshSearchLineInterface::metaObject() const
{
    return &staticMetaObject;
}

void *NutshSearchLineInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NutshSearchLineInterface))
        return static_cast<void*>(const_cast< NutshSearchLineInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int NutshSearchLineInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showResults((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
