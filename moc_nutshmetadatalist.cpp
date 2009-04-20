/****************************************************************************
** Meta object code from reading C++ file 'nutshmetadatalist.h'
**
** Created: Sun Apr 12 21:47:04 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nutshmetadatalist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nutshmetadatalist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NutshMetaDataList[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      33,   18,   19,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      56,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NutshMetaDataList[] = {
    "NutshMetaDataList\0\0NutshMetaData\0"
    "clicked(NutshMetaData)\0emitSignal(QModelIndex)\0"
};

const QMetaObject NutshMetaDataList::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_NutshMetaDataList,
      qt_meta_data_NutshMetaDataList, 0 }
};

const QMetaObject *NutshMetaDataList::metaObject() const
{
    return &staticMetaObject;
}

void *NutshMetaDataList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NutshMetaDataList))
        return static_cast<void*>(const_cast< NutshMetaDataList*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int NutshMetaDataList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { NutshMetaData _r = clicked((*reinterpret_cast< NutshMetaData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NutshMetaData*>(_a[0]) = _r; }  break;
        case 1: emitSignal((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
NutshMetaData NutshMetaDataList::clicked(NutshMetaData _t1)
{
    NutshMetaData _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
