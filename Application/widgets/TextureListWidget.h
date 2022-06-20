#ifndef TEXTURELISTWIDGET_H_
#define TEXTURELISTWIDGET_H_

#include "WidgetBase.h"

class TextureListWidget : public WidgetBase
{
public:

	explicit TextureListWidget();
	virtual ~TextureListWidget() = default;

	virtual void onRun() override;
};

#endif // !TEXTURELISTWIDGET_H_
