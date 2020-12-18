#pragma once
#include "IInput.h"

#include <vector>

class OpenGLInput : public IInput
{
protected:
	std::vector<handlerCallbackType> keyHandlers_;
public:
	~OpenGLInput() = default;
	void ProcessInput() override;
	void GetKeyDown(int key) override;
	void GetKey(int key) override;
	void AddHandler(int key, handlerCallbackType callback) override;
};