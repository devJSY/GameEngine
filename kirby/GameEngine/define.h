#pragma once

// Singleton

#define SINGLE(type) public: \
				static type* GetInst()\
				{\
						static type inst;\
						return &inst;\
				}\
				private:\
					type();\
					~type();\

