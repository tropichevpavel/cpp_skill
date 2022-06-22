#pragma once

class IElectronic {

public:
	virtual void showSpec() = 0;
	virtual ~IElectronic() = default;
};
