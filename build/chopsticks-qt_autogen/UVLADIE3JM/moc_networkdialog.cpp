/****************************************************************************
** Meta object code from reading C++ file 'networkdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/networkdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkDialog_t {
    QByteArrayData data[19];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkDialog_t qt_meta_stringdata_NetworkDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NetworkDialog"
QT_MOC_LITERAL(1, 14, 14), // "gameConfigured"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "GameType"
QT_MOC_LITERAL(4, 39, 8), // "gameType"
QT_MOC_LITERAL(5, 48, 24), // "NetworkManager::GameMode"
QT_MOC_LITERAL(6, 73, 11), // "networkMode"
QT_MOC_LITERAL(7, 85, 7), // "address"
QT_MOC_LITERAL(8, 93, 4), // "port"
QT_MOC_LITERAL(9, 98, 12), // "aiDifficulty"
QT_MOC_LITERAL(10, 111, 13), // "onModeChanged"
QT_MOC_LITERAL(11, 125, 13), // "onStartServer"
QT_MOC_LITERAL(12, 139, 17), // "onConnectToServer"
QT_MOC_LITERAL(13, 157, 17), // "onClientConnected"
QT_MOC_LITERAL(14, 175, 10), // "clientInfo"
QT_MOC_LITERAL(15, 186, 19), // "onConnectedToServer"
QT_MOC_LITERAL(16, 206, 17), // "onConnectionError"
QT_MOC_LITERAL(17, 224, 5), // "error"
QT_MOC_LITERAL(18, 230, 16) // "updateServerInfo"

    },
    "NetworkDialog\0gameConfigured\0\0GameType\0"
    "gameType\0NetworkManager::GameMode\0"
    "networkMode\0address\0port\0aiDifficulty\0"
    "onModeChanged\0onStartServer\0"
    "onConnectToServer\0onClientConnected\0"
    "clientInfo\0onConnectedToServer\0"
    "onConnectionError\0error\0updateServerInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   65,    2, 0x08 /* Private */,
      11,    0,   66,    2, 0x08 /* Private */,
      12,    0,   67,    2, 0x08 /* Private */,
      13,    1,   68,    2, 0x08 /* Private */,
      15,    0,   71,    2, 0x08 /* Private */,
      16,    1,   72,    2, 0x08 /* Private */,
      18,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::QString, QMetaType::UShort, QMetaType::Int,    4,    6,    7,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

       0        // eod
};

void NetworkDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gameConfigured((*reinterpret_cast< GameType(*)>(_a[1])),(*reinterpret_cast< NetworkManager::GameMode(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< quint16(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 1: _t->onModeChanged(); break;
        case 2: _t->onStartServer(); break;
        case 3: _t->onConnectToServer(); break;
        case 4: _t->onClientConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onConnectedToServer(); break;
        case 6: _t->onConnectionError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->updateServerInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkDialog::*)(GameType , NetworkManager::GameMode , const QString & , quint16 , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkDialog::gameConfigured)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetworkDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_NetworkDialog.data,
    qt_meta_data_NetworkDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetworkDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int NetworkDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void NetworkDialog::gameConfigured(GameType _t1, NetworkManager::GameMode _t2, const QString & _t3, quint16 _t4, int _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
