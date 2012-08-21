#ifndef MODEXEPLUS_H
#define MODEXEPLUS_H

#include "ModelPlus.h"
#include <QFileInfoList>


class ExeModel;

class ModExePlus : public ModelPlus

{
    Q_OBJECT


public :


    ModExePlus(Project*,QString modModelName);
    ModExePlus(Project*,const QDomElement & );
    virtual ~ModExePlus();

    virtual QString getClassName(){return ModExePlus::className();}
    static QString className(){return "ModExePlus";}

    // model type
    virtual ModelType modelType(){return ModelPlus::EXECUTABLE;}

    // files
    QFileInfo exeFile();
    QFileInfo inputFile();

    //*************************
    // Get / Set functions
    //*************************

    ExeModel* modModel();


    void setModModelName(QString);

    //*************************
    // Path functions
    //*************************
    virtual QDomElement toXmlData(QDomDocument &doc);

    //*************************
    // Read functions
    //*************************
    bool readAll(ModPlusCtrl*);

    //************************
    //  Main functions
    //************************
    virtual void clear();
    virtual void save();


    //************************
    //  Execution functions
    //************************
    bool isCompiled(ModPlusCtrl* ctrl);

public slots :
    bool compile(ModPlusCtrl* ctrl);


    //************************
    // Others
    //************************
    virtual bool readVariables(ModPlusCtrl*, bool forceRecompile = false);
    bool variablesRead() const;

};







#endif // MODEXEPLUS_H
