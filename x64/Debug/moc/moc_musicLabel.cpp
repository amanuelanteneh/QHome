/****************************************************************************
** Meta object code from reading C++ file 'musicLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/musicLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_musicLabel_t {
    QByteArrayData data[16];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_musicLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_musicLabel_t qt_meta_stringdata_musicLabel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "musicLabel"
QT_MOC_LITERAL(1, 11, 10), // "pauseMusic"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "playMusic"
QT_MOC_LITERAL(4, 33, 10), // "startMusic"
QT_MOC_LITERAL(5, 44, 9), // "nextMusic"
QT_MOC_LITERAL(6, 54, 9), // "prevMusic"
QT_MOC_LITERAL(7, 64, 10), // "queueMusic"
QT_MOC_LITERAL(8, 75, 12), // "currentMusic"
QT_MOC_LITERAL(9, 88, 12), // "changeVolume"
QT_MOC_LITERAL(10, 101, 27), // "authenticationStatusChanged"
QT_MOC_LITERAL(11, 129, 22), // "QAbstractOAuth::Status"
QT_MOC_LITERAL(12, 152, 6), // "status"
QT_MOC_LITERAL(13, 159, 16), // "changeToAlbumArt"
QT_MOC_LITERAL(14, 176, 15), // "refreshAlbumArt"
QT_MOC_LITERAL(15, 192, 22) // "checkForPlaybackChange"

    },
    "musicLabel\0pauseMusic\0\0playMusic\0"
    "startMusic\0nextMusic\0prevMusic\0"
    "queueMusic\0currentMusic\0changeVolume\0"
    "authenticationStatusChanged\0"
    "QAbstractOAuth::Status\0status\0"
    "changeToAlbumArt\0refreshAlbumArt\0"
    "checkForPlaybackChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_musicLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    1,   82,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void musicLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<musicLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pauseMusic(); break;
        case 1: _t->playMusic(); break;
        case 2: _t->startMusic(); break;
        case 3: _t->nextMusic(); break;
        case 4: _t->prevMusic(); break;
        case 5: _t->queueMusic(); break;
        case 6: _t->currentMusic(); break;
        case 7: _t->changeVolume(); break;
        case 8: _t->authenticationStatusChanged((*reinterpret_cast< QAbstractOAuth::Status(*)>(_a[1]))); break;
        case 9: _t->changeToAlbumArt(); break;
        case 10: _t->refreshAlbumArt(); break;
        case 11: _t->checkForPlaybackChange(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject musicLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_musicLabel.data,
    qt_meta_data_musicLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *musicLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *musicLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_musicLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int musicLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
