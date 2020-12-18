/****************************************************************************
** Meta object code from reading C++ file 'bluetoothLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/bluetoothLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bluetoothLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_bluetoothLabel_t {
    QByteArrayData data[19];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_bluetoothLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_bluetoothLabel_t qt_meta_stringdata_bluetoothLabel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "bluetoothLabel"
QT_MOC_LITERAL(1, 15, 7), // "clicked"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "released"
QT_MOC_LITERAL(4, 33, 9), // "connected"
QT_MOC_LITERAL(5, 43, 12), // "disconnected"
QT_MOC_LITERAL(6, 56, 16), // "deviceDiscovered"
QT_MOC_LITERAL(7, 73, 20), // "QBluetoothDeviceInfo"
QT_MOC_LITERAL(8, 94, 6), // "device"
QT_MOC_LITERAL(9, 101, 12), // "finishedScan"
QT_MOC_LITERAL(10, 114, 22), // "deviceAdditionSelected"
QT_MOC_LITERAL(11, 137, 15), // "deviceConnected"
QT_MOC_LITERAL(12, 153, 18), // "deviceDisconnected"
QT_MOC_LITERAL(13, 172, 9), // "addDevice"
QT_MOC_LITERAL(14, 182, 13), // "deviceOptions"
QT_MOC_LITERAL(15, 196, 12), // "removeDevice"
QT_MOC_LITERAL(16, 209, 16), // "bluetoothDevice1"
QT_MOC_LITERAL(17, 226, 16), // "bluetoothDevice2"
QT_MOC_LITERAL(18, 243, 16) // "bluetoothDevice3"

    },
    "bluetoothLabel\0clicked\0\0released\0"
    "connected\0disconnected\0deviceDiscovered\0"
    "QBluetoothDeviceInfo\0device\0finishedScan\0"
    "deviceAdditionSelected\0deviceConnected\0"
    "deviceDisconnected\0addDevice\0deviceOptions\0"
    "removeDevice\0bluetoothDevice1\0"
    "bluetoothDevice2\0bluetoothDevice3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_bluetoothLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    0,   91,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   93,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,
      17,    0,  104,    2, 0x08 /* Private */,
      18,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void bluetoothLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<bluetoothLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->released(); break;
        case 2: _t->connected(); break;
        case 3: _t->disconnected(); break;
        case 4: _t->deviceDiscovered((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 5: _t->finishedScan(); break;
        case 6: _t->deviceAdditionSelected(); break;
        case 7: _t->deviceConnected(); break;
        case 8: _t->deviceDisconnected(); break;
        case 9: _t->addDevice(); break;
        case 10: _t->deviceOptions(); break;
        case 11: _t->removeDevice(); break;
        case 12: _t->bluetoothDevice1(); break;
        case 13: _t->bluetoothDevice2(); break;
        case 14: _t->bluetoothDevice3(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothDeviceInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (bluetoothLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&bluetoothLabel::clicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (bluetoothLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&bluetoothLabel::released)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (bluetoothLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&bluetoothLabel::connected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (bluetoothLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&bluetoothLabel::disconnected)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject bluetoothLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_bluetoothLabel.data,
    qt_meta_data_bluetoothLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *bluetoothLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *bluetoothLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_bluetoothLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int bluetoothLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void bluetoothLabel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void bluetoothLabel::released()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void bluetoothLabel::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void bluetoothLabel::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
