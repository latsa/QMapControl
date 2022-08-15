/****************************************************************************
** Meta object code from reading C++ file 'Navigator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Navigator/Navigator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Navigator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Navigator_t {
    QByteArrayData data[19];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Navigator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Navigator_t qt_meta_stringdata_Navigator = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Navigator"
QT_MOC_LITERAL(1, 10, 19), // "onActionRecordPoint"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "onActionSavePath"
QT_MOC_LITERAL(4, 48, 16), // "onActionLoadPath"
QT_MOC_LITERAL(5, 65, 21), // "onActionLoadShapefile"
QT_MOC_LITERAL(6, 87, 16), // "onActionLoadTiff"
QT_MOC_LITERAL(7, 104, 16), // "onActionPlayPath"
QT_MOC_LITERAL(8, 121, 15), // "onCourseChanged"
QT_MOC_LITERAL(9, 137, 9), // "newcourse"
QT_MOC_LITERAL(10, 147, 7), // "animate"
QT_MOC_LITERAL(11, 155, 10), // "updatePath"
QT_MOC_LITERAL(12, 166, 20), // "mapFocusPointChanged"
QT_MOC_LITERAL(13, 187, 28), // "qmapcontrol::PointWorldCoord"
QT_MOC_LITERAL(14, 216, 12), // "mapMouseMove"
QT_MOC_LITERAL(15, 229, 12), // "QMouseEvent*"
QT_MOC_LITERAL(16, 242, 18), // "mapRotationChanged"
QT_MOC_LITERAL(17, 261, 13), // "courseDegrees"
QT_MOC_LITERAL(18, 275, 16) // "updateLayersMenu"

    },
    "Navigator\0onActionRecordPoint\0\0"
    "onActionSavePath\0onActionLoadPath\0"
    "onActionLoadShapefile\0onActionLoadTiff\0"
    "onActionPlayPath\0onCourseChanged\0"
    "newcourse\0animate\0updatePath\0"
    "mapFocusPointChanged\0qmapcontrol::PointWorldCoord\0"
    "mapMouseMove\0QMouseEvent*\0mapRotationChanged\0"
    "courseDegrees\0updateLayersMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Navigator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    1,   85,    2, 0x0a /* Public */,
      10,    0,   88,    2, 0x0a /* Public */,
      11,    0,   89,    2, 0x0a /* Public */,
      12,    1,   90,    2, 0x0a /* Public */,
      14,    3,   93,    2, 0x0a /* Public */,
      16,    1,  100,    2, 0x0a /* Public */,
      18,    0,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 13, 0x80000000 | 13,    2,    2,    2,
    QMetaType::Void, QMetaType::QReal,   17,
    QMetaType::Void,

       0        // eod
};

void Navigator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Navigator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onActionRecordPoint(); break;
        case 1: _t->onActionSavePath(); break;
        case 2: _t->onActionLoadPath(); break;
        case 3: _t->onActionLoadShapefile(); break;
        case 4: _t->onActionLoadTiff(); break;
        case 5: _t->onActionPlayPath(); break;
        case 6: _t->onCourseChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->animate(); break;
        case 8: _t->updatePath(); break;
        case 9: _t->mapFocusPointChanged((*reinterpret_cast< qmapcontrol::PointWorldCoord(*)>(_a[1]))); break;
        case 10: _t->mapMouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< qmapcontrol::PointWorldCoord(*)>(_a[2])),(*reinterpret_cast< qmapcontrol::PointWorldCoord(*)>(_a[3]))); break;
        case 11: _t->mapRotationChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 12: _t->updateLayersMenu(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Navigator::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Navigator.data,
    qt_meta_data_Navigator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Navigator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Navigator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Navigator.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Navigator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
