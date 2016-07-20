/****************************************************************************
** Meta object code from reading C++ file 'PauseMenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/gui/PauseMenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PauseMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PauseMenu_t {
    QByteArrayData data[5];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PauseMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PauseMenu_t qt_meta_stringdata_PauseMenu = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PauseMenu"
QT_MOC_LITERAL(1, 10, 19), // "ResumeButtonPressed"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "SaveButtonPressed"
QT_MOC_LITERAL(4, 49, 21) // "QuitGameButtonPressed"

    },
    "PauseMenu\0ResumeButtonPressed\0\0"
    "SaveButtonPressed\0QuitGameButtonPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PauseMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PauseMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PauseMenu *_t = static_cast<PauseMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ResumeButtonPressed(); break;
        case 1: _t->SaveButtonPressed(); break;
        case 2: _t->QuitGameButtonPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PauseMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PauseMenu::ResumeButtonPressed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PauseMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PauseMenu::SaveButtonPressed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PauseMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PauseMenu::QuitGameButtonPressed)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PauseMenu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PauseMenu.data,
      qt_meta_data_PauseMenu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PauseMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PauseMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PauseMenu.stringdata0))
        return static_cast<void*>(const_cast< PauseMenu*>(this));
    return QWidget::qt_metacast(_clname);
}

int PauseMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PauseMenu::ResumeButtonPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PauseMenu::SaveButtonPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void PauseMenu::QuitGameButtonPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
