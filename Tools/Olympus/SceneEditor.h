////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   SceneEditor.h
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QWidget>
#include <Qt/qgl.h>

#ifdef Q_WS_WIN

class SceneEditorD3D11 : public QWidget
{
    Q_OBJECT
    
public:
    SceneEditorD3D11(QWidget* pkParent = 0);
    ~SceneEditorD3D11();

protected:
    QPaintEngine* paintEngine() const;

    void paintEvent(QPaintEvent*);

    void resizeEvent(QResizeEvent* pkEvent);

private slots:
    void OnUpdateFrame();

};

#endif

class SceneEditorOGL : public QGLWidget
{
    Q_OBJECT

public:
    SceneEditorOGL(QWidget* pkParent = 0);
    ~SceneEditorOGL();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int iWidth, int iHeight);
};
