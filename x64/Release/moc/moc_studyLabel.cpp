/****************************************************************************
** Meta object code from reading C++ file 'studyLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/studyLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'studyLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_studyLabel_t {
    QByteArrayData data[13];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_studyLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_studyLabel_t qt_meta_stringdata_studyLabel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "studyLabel"
QT_MOC_LITERAL(1, 11, 7), // "clicked"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "released"
QT_MOC_LITERAL(4, 29, 10), // "closeEvent"
QT_MOC_LITERAL(5, 40, 12), // "studyOption1"
QT_MOC_LITERAL(6, 53, 12), // "studyOption2"
QT_MOC_LITERAL(7, 66, 12), // "studyOption3"
QT_MOC_LITERAL(8, 79, 12), // "studyOption4"
QT_MOC_LITERAL(9, 92, 12), // "studyOption5"
QT_MOC_LITERAL(10, 105, 12), // "studyOption6"
QT_MOC_LITERAL(11, 118, 16), // "configureClasses"
QT_MOC_LITERAL(12, 135, 20) // "deleteOptionSelected"

    },
    "studyLabel\0clicked\0\0released\0closeEvent\0"
    "studyOption1\0studyOption2\0studyOption3\0"
    "studyOption4\0studyOption5\0studyOption6\0"
    "configureClasses\0deleteOptionSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_studyLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
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

void studyLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<studyLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->released(); break;
        case 2: _t->closeEvent(); break;
        case 3: _t->studyOption1(); break;
        case 4: _t->studyOption2(); break;
        case 5: _t->studyOption3(); break;
        case 6: _t->studyOption4(); break;
        case 7: _t->studyOption5(); break;
        case 8: _t->studyOption6(); break;
        case 9: _t->configureClasses(); break;
        case 10: _t->deleteOptionSelected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (studyLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&studyLabel::clicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (studyLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&studyLabel::released)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (studyLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&studyLabel::closeEvent)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject studyLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_studyLabel.data,
    qt_meta_data_studyLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *studyLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *studyLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_studyLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int studyLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void studyLabel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void studyLabel::released()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void studyLabel::closeEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
