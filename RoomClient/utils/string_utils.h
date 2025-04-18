/**
 * This file is part of mediasoup_client project.
 * Author:    Jackie Ou
 * Created:   2021-11-01
 **/

#ifndef ROOMCLIENT_UTILS_STRING_UTILS_H_
#define ROOMCLIENT_UTILS_STRING_UTILS_H_
#include <string>

namespace vi
{
	class StringUtils
	{
	public:
		// Helper method to create random identifiers (e.g., transaction)
		static std::string randomString(int32_t len);
	};

}
#endif // !ROOMCLIENT_UTILS_STRING_UTILS_H_