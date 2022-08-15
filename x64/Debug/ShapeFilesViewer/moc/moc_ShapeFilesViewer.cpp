/****************************************************************************
** Meta object code from reading C++ file 'ShapeFilesViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../ShapeFilesViewer/ShapeFilesViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShapeFilesViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ShapeFilesViewer_t {
    QByteArrayData data[11];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShapeFilesViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShapeFilesViewer_t qt_meta_stringdata_ShapeFilesViewer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ShapeFilesViewer"
QT_MOC_LITERAL(1, 17, 26), // "onShapefileFeaturesClicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 24), // "std::vector<OGRFeature*>"
QT_MOC_LITERAL(4, 70, 8), // "features"
QT_MOC_LITERAL(5, 79, 15), // "onLoadShapeFile"
QT_MOC_LITERAL(6, 95, 14), // "onLoadTiffFile"
QT_MOC_LITERAL(7, 110, 20), // "mapFocusPointChanged"
QT_MOC_LITERAL(8, 131, 28), // "qmapcontrol::PointWorldCoord"
QT_MOC_LITERAL(9, 160, 12), // "mapMouseMove"
QT_MOC_LITERAL(10, 173, 12) // "QMouseEvent*"

    },
    "ShapeFilesViewer\0onShapefileFeaturesClicked\0"
    "\0std::vector<OGRFeature*>\0features\0"
    "onLoadShapeFile\0onLoadTiffFile\0"
    "mapFocusPointChanged\0qmapcontrol::PointWorldCoord\0"
    "mapMouseMove\0QMouseEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShapeFilesViewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,
       7,    1,   44,    2, 0x0a /* Public */,
       9,    3,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 8, 0x80000000 | 8,    2,    2,    2,

       0        // eod
};

void ShapeFilesViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShapeFilesViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onShapefileFeaturesClicked((*reinterpret_cast< std::vector<OGRFeature*>(*)>(_a[1]))); break;
        case 1: _t->onLoadShapeFile(); break;
        case 2: _t->onLoadTiffFile(); break;
        case 3: _t->mapFocusPointChanged((*reinterpret_cast< qmapcontrol::PointWorldCoord(*)>(_a[1]))); break;
        case 4: _t->mapMouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< qmapcontrol::PointWorldCoord(*)>(_a[2])),(*reinterpret_cast< qmapcontrol::PointWorldCoord(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ShapeFilesViewer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ShapeFilesViewer.data,
    qt_meta_data_ShapeFilesViewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ShapeFilesViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShapeFilesViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ShapeFilesViewer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ShapeFilesViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
