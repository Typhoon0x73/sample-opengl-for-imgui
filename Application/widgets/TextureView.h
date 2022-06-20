#ifndef TEXTUREVIEW_H_
#define TEXTUREVIEW_H_

#include "WidgetBase.h"

class TextureView : public WidgetBase
{
public:

	explicit TextureView();
	virtual ~TextureView() = default;

	virtual void onRun() override;
};

#endif // !TEXTUREVIEW_H_
