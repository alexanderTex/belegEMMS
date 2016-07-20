/****************************************************************************
** Meta object code from reading C++ file 'GameManagerThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/core/GameManagerThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameManagerThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameManager_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameManager_t qt_meta_stringdata_GameManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GameManager"
QT_MOC_LITERAL(1, 12, 19), // "PlayInputErrorSound"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 20), // "PlayInputAcceptSound"
QT_MOC_LITERAL(4, 54, 12), // "TurnFinished"
QT_MOC_LITERAL(5, 67, 9) // "PlayerWon"

    },
    "GameManager\0PlayInputErrorSound\0\0"
    "PlayInputAcceptSound\0TurnFinished\0"
    "PlayerWon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GameManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameManager *_t = static_cast<GameManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PlayInputErrorSound(); break;
        case 1: _t->PlayInputAcceptSound(); break;
        case 2: _t->TurnFinished(); break;
        case 3: _t->PlayerWon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GameManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameManager::PlayInputErrorSound)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GameManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameManager::PlayInputAcceptSound)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GameManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameManager::TurnFinished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GameManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameManager::PlayerWon)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GameManager::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GameManager.data,
      qt_meta_data_GameManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GameManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GameManager.stringdata0))
        return static_cast<void*>(const_cast< GameManager*>(this));
    return QThread::qt_metacast(_clname);
}

int GameManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GameManager::PlayInputErrorSound()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void GameManager::PlayInputAcceptSound()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void GameManager::TurnFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void GameManager::PlayerWon()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
