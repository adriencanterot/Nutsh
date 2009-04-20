/****************************************************************************
** Meta object code from reading C++ file 'nutshplayinginterface.h'
**
** Created: Sun Apr 12 21:47:04 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nutshplayinginterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nutshplayinginterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NutshPlayingInterface[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x0a,
      30,   22,   22,   22, 0x0a,
      41,   22,   22,   22, 0x0a,
      58,   53,   22,   22, 0x0a,
      71,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NutshPlayingInterface[] = {
    "NutshPlayingInterface\0\0next()\0previous()\0"
    "playPause()\0time\0tick(qint64)\0stop()\0"
};

const QMetaObject NutshPlayingInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NutshPlayingInterface,
      qt_meta_data_NutshPlayingInterface, 0 }
};

const QMetaObject *NutshPlayingInterface::metaObject() const
{
    return &staticMetaObject;
}

void *NutshPlayingInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NutshPlayingInterface))
        return static_cast<void*>(const_cast< NutshPlayingInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int NutshPlayingInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: next(); break;
        case 1: previous(); break;
        case 2: playPause(); break;
        case 3: tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: stop(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
