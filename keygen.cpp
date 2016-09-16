#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Crypto.h"
#include "Identity.h"

int main (int argc, char * argv[])
{
	if (argc < 3)
	{
		std::cout << "Usage: keygen filename <signuture type>" << std::endl;	
		return -1;
	}
	i2p::crypto::InitCrypto (false);
	i2p::data::SigningKeyType type = i2p::data::SIGNING_KEY_TYPE_DSA_SHA1;	
	if (argc >= 3) type = atoi (argv[2]);
	auto keys = i2p::data::PrivateKeys::CreateRandomKeys (type);
	std::ofstream f (argv[1], std::ofstream::binary | std::ofstream::out);
	if (f)
	{
		size_t len = keys.GetFullLen ();
		uint8_t * buf = new uint8_t[len];
		len = keys.ToBuffer (buf, len);
		f.write ((char *)buf, len);
		delete[] buf;
		std::cout << "Destination " << keys.GetPublic ()->GetIdentHash ().ToBase32 () << " created" << std::endl;
	}
	else
		std::cout << "Can't create file " << argv[1] << std::endl;	

	return 0;
}

