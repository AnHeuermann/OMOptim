/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2017, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */
/*
 * @author Adeel Asghar <adeel.asghar@liu.se>
 * @author Adrian Pop <adrian.pop@liu.se>
 */



#include "Utilities.h"
#include <QProcessEnvironment>

/*!
 * \brief Utilities::tempDirectory
 * Returns the application temporary directory.
 * \return
 */
QString& Utilities::tempDirectory()
{
  static int init = 0;
  static QString tmpPath;
  if (!init) {
    init = 1;
#ifdef WIN32
    tmpPath = QDir::tempPath() + "/OpenModelica/OMOptim/";
#else // UNIX environment
    char *user = getenv("USER");
    tmpPath = QDir::tempPath() + "/OpenModelica_" + QString(user ? user : "nobody") + "/OMOptim/";
#endif
    tmpPath.remove("\"");
    if (!QDir().exists(tmpPath))
      QDir().mkpath(tmpPath);
  }
  return tmpPath;
}

QString& Utilities::getOMLog()
{
  static QString OMLogPath = tempDirectory() + QDir::separator() + "OMLog.txt";
  return OMLogPath;
}

QString& Utilities::getOMScriptLog()
{
  static QString OMScriptLogPath = tempDirectory() + QDir::separator() + "OMScriptLog.txt";
  return OMScriptLogPath;
}


QString& Utilities::getMinGWBinPath()
{
    static QString mingw;
#ifdef WIN32
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString om = env.value("OPENMODELICAHOME");
    QString omHome = om + QString("/bin");
    QString omdev = env.value("OMDEV");
    QString omdev_msys = env.value("OMDEV_MSYS");
    QString ucrt64msys2 = "tools/msys64/mingw64/bin";
    // Try OM first
    if (QDir(om + QDir::separator() + ucrt64msys2).exists())
    {
      mingw = om + QDir::separator() + ucrt64msys2;
    }
    // Try OMDEV_MSYS
    else if (QDir(omdev_msys + QDir::separator() + "/bin").exists())
    {
      mingw = omdev_msys + QDir::separator() + "/bin";
    }
    // Try OMDEV
    else if (QDir(omdev + QDir::separator() + ucrt64msys2).exists())
    {
      mingw = omdev + QDir::separator() + ucrt64msys2;
    }

    // Default value if nothing found
    if (mingw.isEmpty()) // assume ucrt64
    {
       mingw = om + QDir::separator() + ucrt64msys2;
    }
#else
    mingw = "";
#endif
    return mingw;
}

QString& Utilities::getOMBinPath()
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    static QString om = env.value("OPENMODELICAHOME") + QDir::separator() + "bin";
    return om;
}
