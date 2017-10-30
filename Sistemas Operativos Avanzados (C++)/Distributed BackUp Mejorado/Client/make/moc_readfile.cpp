/****************************************************************************
** Meta object code from reading C++ file 'readfile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../readfile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'readfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReadFile_t {
    QByteArrayData data[19];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReadFile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReadFile_t qt_meta_stringdata_ReadFile = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ReadFile"
QT_MOC_LITERAL(1, 9, 4), // "Send"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 3), // "out"
QT_MOC_LITERAL(4, 19, 15), // "UpdateTotalSize"
QT_MOC_LITERAL(5, 35, 4), // "size"
QT_MOC_LITERAL(6, 40, 19), // "UpdateTotalFileSize"
QT_MOC_LITERAL(7, 60, 19), // "UpdateCurrentSizeRW"
QT_MOC_LITERAL(8, 80, 23), // "UpdateCurrentFileSizeRW"
QT_MOC_LITERAL(9, 104, 10), // "UpdateName"
QT_MOC_LITERAL(10, 115, 4), // "name"
QT_MOC_LITERAL(11, 120, 6), // "insert"
QT_MOC_LITERAL(12, 127, 4), // "Read"
QT_MOC_LITERAL(13, 132, 3), // "Dir"
QT_MOC_LITERAL(14, 136, 4), // "Name"
QT_MOC_LITERAL(15, 141, 15), // "UpdatePauseTime"
QT_MOC_LITERAL(16, 157, 4), // "msec"
QT_MOC_LITERAL(17, 162, 4), // "NACK"
QT_MOC_LITERAL(18, 167, 4) // "data"

    },
    "ReadFile\0Send\0\0out\0UpdateTotalSize\0"
    "size\0UpdateTotalFileSize\0UpdateCurrentSizeRW\0"
    "UpdateCurrentFileSizeRW\0UpdateName\0"
    "name\0insert\0Read\0Dir\0Name\0UpdatePauseTime\0"
    "msec\0NACK\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReadFile[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    1,   70,    2, 0x06 /* Public */,
       7,    1,   73,    2, 0x06 /* Public */,
       8,    1,   76,    2, 0x06 /* Public */,
       9,    1,   79,    2, 0x06 /* Public */,
      11,    2,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   87,    2, 0x0a /* Public */,
      15,    1,   92,    2, 0x0a /* Public */,
      17,    1,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   10,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   13,   14,
    QMetaType::Void, QMetaType::ULong,   16,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void ReadFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ReadFile *_t = static_cast<ReadFile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Send((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->UpdateTotalSize((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: _t->UpdateTotalFileSize((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->UpdateCurrentSizeRW((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->UpdateCurrentFileSizeRW((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->UpdateName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->insert((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->Read((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->UpdatePauseTime((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 9: _t->NACK((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ReadFile::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadFile::Send)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ReadFile::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadFile::UpdateTotalSize)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ReadFile::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadFile::UpdateTotalFileSize)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ReadFile::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadFile::UpdateCurrentSizeRW)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ReadFile::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadFile::UpdateCurrentFileSizeRW)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ReadFile::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadFile::UpdateName)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ReadFile::*_t)(QString , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadFile::insert)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject ReadFile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReadFile.data,
      qt_meta_data_ReadFile,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ReadFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReadFile::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ReadFile.stringdata0))
        return static_cast<void*>(const_cast< ReadFile*>(this));
    return QObject::qt_metacast(_clname);
}

int ReadFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ReadFile::Send(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ReadFile::UpdateTotalSize(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ReadFile::UpdateTotalFileSize(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ReadFile::UpdateCurrentSizeRW(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ReadFile::UpdateCurrentFileSizeRW(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ReadFile::UpdateName(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ReadFile::insert(QString _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
