/****************************************************************************
** Meta object code from reading C++ file 'citymap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Citymap/citymap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'citymap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Citymap_t {
    QByteArrayData data[19];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Citymap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Citymap_t qt_meta_stringdata_Citymap = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Citymap"
QT_MOC_LITERAL(1, 8, 15), // "geometryClicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "const Geometry*"
QT_MOC_LITERAL(4, 41, 8), // "geometry"
QT_MOC_LITERAL(5, 50, 18), // "geometryClickedPub"
QT_MOC_LITERAL(6, 69, 7), // "addNote"
QT_MOC_LITERAL(7, 77, 9), // "writeNote"
QT_MOC_LITERAL(8, 87, 12), // "QMouseEvent*"
QT_MOC_LITERAL(9, 100, 11), // "mouse_event"
QT_MOC_LITERAL(10, 112, 15), // "PointWorldCoord"
QT_MOC_LITERAL(11, 128, 16), // "press_coordinate"
QT_MOC_LITERAL(12, 145, 8), // "hideNote"
QT_MOC_LITERAL(13, 154, 8), // "editNote"
QT_MOC_LITERAL(14, 163, 17), // "calculateDistance"
QT_MOC_LITERAL(15, 181, 22), // "calculateDistanceClick"
QT_MOC_LITERAL(16, 204, 19), // "mapProviderSelected"
QT_MOC_LITERAL(17, 224, 8), // "QAction*"
QT_MOC_LITERAL(18, 233, 6) // "action"

    },
    "Citymap\0geometryClicked\0\0const Geometry*\0"
    "geometry\0geometryClickedPub\0addNote\0"
    "writeNote\0QMouseEvent*\0mouse_event\0"
    "PointWorldCoord\0press_coordinate\0"
    "hideNote\0editNote\0calculateDistance\0"
    "calculateDistanceClick\0mapProviderSelected\0"
    "QAction*\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Citymap[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       6,    0,   65,    2, 0x08 /* Private */,
       7,    2,   66,    2, 0x08 /* Private */,
      12,    2,   71,    2, 0x08 /* Private */,
      13,    1,   76,    2, 0x08 /* Private */,
      14,    0,   79,    2, 0x08 /* Private */,
      15,    2,   80,    2, 0x08 /* Private */,
      16,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void Citymap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Citymap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->geometryClicked((*reinterpret_cast< const Geometry*(*)>(_a[1]))); break;
        case 1: _t->geometryClickedPub((*reinterpret_cast< const Geometry*(*)>(_a[1]))); break;
        case 2: _t->addNote(); break;
        case 3: _t->writeNote((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< PointWorldCoord(*)>(_a[2]))); break;
        case 4: _t->hideNote((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< PointWorldCoord(*)>(_a[2]))); break;
        case 5: _t->editNote((*reinterpret_cast< const Geometry*(*)>(_a[1]))); break;
        case 6: _t->calculateDistance(); break;
        case 7: _t->calculateDistanceClick((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< PointWorldCoord(*)>(_a[2]))); break;
        case 8: _t->mapProviderSelected((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Citymap::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Citymap.data,
    qt_meta_data_Citymap,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Citymap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Citymap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Citymap.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Citymap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
