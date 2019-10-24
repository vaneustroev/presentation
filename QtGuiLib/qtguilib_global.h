#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTGUILIB_LIB)
#  define QTGUILIB_EXPORT Q_DECL_EXPORT
# else
#  define QTGUILIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTGUILIB_EXPORT
#endif
