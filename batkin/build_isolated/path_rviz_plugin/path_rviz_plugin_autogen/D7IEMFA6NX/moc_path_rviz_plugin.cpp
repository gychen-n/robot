/****************************************************************************
** Meta object code from reading C++ file 'path_rviz_plugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/navigation/path_rviz_plugin/include/path_rviz_plugin/path_rviz_plugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'path_rviz_plugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_autolabor_plugin__PathRvizPlugin_t {
    QByteArrayData data[6];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_autolabor_plugin__PathRvizPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_autolabor_plugin__PathRvizPlugin_t qt_meta_stringdata_autolabor_plugin__PathRvizPlugin = {
    {
QT_MOC_LITERAL(0, 0, 32), // "autolabor_plugin::PathRvizPlugin"
QT_MOC_LITERAL(1, 33, 21), // "start_record_callback"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 20), // "stop_record_callback"
QT_MOC_LITERAL(4, 77, 19), // "start_task_callback"
QT_MOC_LITERAL(5, 97, 18) // "stop_task_callback"

    },
    "autolabor_plugin::PathRvizPlugin\0"
    "start_record_callback\0\0stop_record_callback\0"
    "start_task_callback\0stop_task_callback"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_autolabor_plugin__PathRvizPlugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x09 /* Protected */,
       3,    0,   35,    2, 0x09 /* Protected */,
       4,    0,   36,    2, 0x09 /* Protected */,
       5,    0,   37,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void autolabor_plugin::PathRvizPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PathRvizPlugin *_t = static_cast<PathRvizPlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start_record_callback(); break;
        case 1: _t->stop_record_callback(); break;
        case 2: _t->start_task_callback(); break;
        case 3: _t->stop_task_callback(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject autolabor_plugin::PathRvizPlugin::staticMetaObject = {
    { &rviz::Panel::staticMetaObject, qt_meta_stringdata_autolabor_plugin__PathRvizPlugin.data,
      qt_meta_data_autolabor_plugin__PathRvizPlugin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *autolabor_plugin::PathRvizPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *autolabor_plugin::PathRvizPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_autolabor_plugin__PathRvizPlugin.stringdata0))
        return static_cast<void*>(const_cast< PathRvizPlugin*>(this));
    return rviz::Panel::qt_metacast(_clname);
}

int autolabor_plugin::PathRvizPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rviz::Panel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE