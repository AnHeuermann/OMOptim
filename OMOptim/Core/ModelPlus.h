#ifndef MODELPLUS_H
#define MODELPLUS_H


#include <QString>
#include <QDomElement>
#include <QFileInfoList>
#include "MOItem.h"


using std::vector;
class Project;
class ModPlusCtrl;
class Variable;
class Variables;
class Info;
class ModModel;
class ModItem;

/**
*
* ModelPlus is a class dedicated to store information concerning models (e.g. files concerned, variables, dependencies...)
* ModelPlus is an abstract class and should be inherited.
*/
class ModelPlus : public MOItem
{
    Q_OBJECT

public :
    enum ModelType
    {
        MODELICA,
        EXECUTABLE
    };
    //******************
    // Attributes
    //******************


protected :
    Variables *_variables; /// List of model variables
    QFileInfoList _neededFiles; /// List of files needed in the simulation folder.
    QFileInfoList _neededFolders; /// List of folders needed in the simulation folder.

    Project* _project;
    QString _modelName;      /// ModelName
    // status booleans
    bool _variablesRead; /// indicates whether variables have been read or not
    QStringList _otherFiles;
    QString _infos;

    QString _mmoFilePath; /// File path of file where all informations are stored


public:

    ModelPlus(Project*,QString modelName);
    ModelPlus(Project* project,const QDomElement &);

    virtual ~ModelPlus();

    virtual QString getClassName(){return ModelPlus::className();}
    static QString className(){return "ModelPlus";}

    // model type
    virtual ModelType modelType() = 0;

    //*************************
    // Get / Set functions
    //*************************
    void setOtherFiles(QStringList);
    QString infos();
    void setInfos(QString);
    QStringList otherFiles();

    void clearOtherFiles();
    QString getFieldName(int,int role){return "-";};
    unsigned getNbFields(){return 0;};
    Project* getProject() ;
    ModModel* modModel();

    void setMmoFilePath(QString);

    QString modelName();
    QFileInfoList neededFiles();
    QFileInfoList neededFolders();
    virtual bool isCompiled(ModPlusCtrl* ctrl) =0;
    QDir mmoFolder();

    virtual QFileInfo mmoFilePath();

    //************************
    //  Main functions
    //************************
    virtual void clear();
    virtual void save();

    //************************
    //  Variables
    //************************
    Variables* variables();
    Variables* variables(ModItem* element);

    //************************
    // Others
    //************************
    virtual QDomElement toXmlData(QDomDocument & doc);

public slots:

    virtual bool readVariables(ModPlusCtrl*, bool forceRecompile=false);
    bool variablesRead() const;


protected :

    //**************************************
    // Variables
    //**************************************
    void addVariable(Variable*);

signals:
    void saved();
    void modified();
    void variablesUpdated();
};





#endif // MODELPLUS_H
