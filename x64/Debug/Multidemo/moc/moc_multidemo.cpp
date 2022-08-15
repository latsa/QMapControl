/****************************************************************************
** Meta object code from reading C++ file 'multidemo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Multidemo/multidemo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multidemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Multidemo_t {
    QByteArrayData data[22];
    char stringdata0[413];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Multidemo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Multidemo_t qt_meta_stringdata_Multidemo = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Multidemo"
QT_MOC_LITERAL(1, 10, 14), // "toggleAddPoint"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "enable"
QT_MOC_LITERAL(4, 33, 14), // "toggleDrawRect"
QT_MOC_LITERAL(5, 48, 15), // "toggleMoveClick"
QT_MOC_LITERAL(6, 64, 9), // "toggleGPS"
QT_MOC_LITERAL(7, 74, 15), // "toggleFollowGPS"
QT_MOC_LITERAL(8, 90, 23), // "geometriesSelectedEvent"
QT_MOC_LITERAL(9, 114, 62), // "std::map<std::string,std::vec..."
QT_MOC_LITERAL(10, 177, 19), // "selected_geometries"
QT_MOC_LITERAL(11, 197, 18), // "geometryClickEvent"
QT_MOC_LITERAL(12, 216, 15), // "const Geometry*"
QT_MOC_LITERAL(13, 232, 8), // "geometry"
QT_MOC_LITERAL(14, 241, 32), // "main_mouseEventReleaseCoordinate"
QT_MOC_LITERAL(15, 274, 12), // "QMouseEvent*"
QT_MOC_LITERAL(16, 287, 11), // "mouse_event"
QT_MOC_LITERAL(17, 299, 15), // "PointWorldCoord"
QT_MOC_LITERAL(18, 315, 16), // "press_coordinate"
QT_MOC_LITERAL(19, 332, 18), // "release_coordinate"
QT_MOC_LITERAL(20, 351, 30), // "main_mouseEventPressCoordinate"
QT_MOC_LITERAL(21, 382, 30) // "mini_mouseEventPressCoordinate"

    },
    "Multidemo\0toggleAddPoint\0\0enable\0"
    "toggleDrawRect\0toggleMoveClick\0toggleGPS\0"
    "toggleFollowGPS\0geometriesSelectedEvent\0"
    "std::map<std::string,std::vector<std::shared_ptr<Geometry> > >\0"
    "selected_geometries\0geometryClickEvent\0"
    "const Geometry*\0geometry\0"
    "main_mouseEventReleaseCoordinate\0"
    "QMouseEvent*\0mouse_event\0PointWorldCoord\0"
    "press_coordinate\0release_coordinate\0"
    "main_mouseEventPressCoordinate\0"
    "mini_mouseEventPressCoordinate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Multidemo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       4,    1,   67,    2, 0x08 /* Private */,
       5,    1,   70,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       7,    1,   76,    2, 0x08 /* Private */,
       8,    1,   79,    2, 0x08 /* Private */,
      11,    1,   82,    2, 0x08 /* Private */,
      14,    3,   85,    2, 0x08 /* Private */,
      20,    2,   92,    2, 0x08 /* Private */,
      21,    2,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17, 0x80000000 | 17,   16,   18,   19,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17,   16,   18,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17,   16,   18,

       0        // eod
};

void Multidemo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Multidemo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toggleAddPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->toggleDrawRect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->toggleMoveClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->toggleGPS((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->toggleFollowGPS((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->geometriesSelectedEvent((*reinterpret_cast< std::map<std::string,std::vector<std::shared_ptr<Geometry> > >(*)>(_a[1]))); break;
        case 6: _t->geometryClickEvent((*reinterpret_cast< const Geometry*(*)>(_a[1]))); break;
        case 7: _t->main_mouseEventReleaseCoordinate((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< PointWorldCoord(*)>(_a[2])),(*reinterpret_cast< PointWorldCoord(*)>(_a[3]))); break;
        case 8: _t->main_mouseEventPressCoordinate((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< PointWorldCoord(*)>(_a[2]))); break;
        case 9: _t->mini_mouseEventPressCoordinate((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< PointWorldCoord(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Multidemo::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Multidemo.data,
    qt_meta_data_Multidemo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Multidemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Multidemo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Multidemo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Multidemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
