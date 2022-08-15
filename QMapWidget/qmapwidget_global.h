#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QMAPWIDGET_LIBRARY)
#  define QMAPWIDGET_EXPORT Q_DECL_EXPORT
# else
#  define QMAPWIDGET_EXPORT Q_DECL_IMPORT
# endif
#else
# define QMAPWIDGET_EXPORT
#endif
