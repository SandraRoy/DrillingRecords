#pragma once
#pragma once
// Do not add or modify anything in this file.

#ifndef HASHER_H
#define HASHER_H

template <typename T>
class Hasher {
public:
	virtual unsigned long hash(const T& item) const = 0;
};

#endif //! HASHER_H