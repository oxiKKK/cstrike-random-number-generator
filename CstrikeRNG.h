// The class simulates the RNG (Random Number Generator) for Counter-Strike 1.6
// It can generate floating-point & integral numbers.
class CCstrikeRNG
{
public:
	template<typename T> requires(std::is_floating_point<T>::value)
	static T RandomFloater(uint32_t Seed, T Low, T High);

	template<typename T> requires(std::is_integral<T>::value)
	static T RandomIntegral(uint32_t Seed, T Low, T High);

private:
	static inline uint32_t AutoSeedorize()
	{
		m_dwSeed *= kMagicConstantMul;
		m_dwSeed += m_dwSeedTable[m_dwSeed & 0xFF] + 1;
		return m_dwSeed & 0xFFFFFFF;
	}

	static inline void Seedorize(uint8_t Seed)
	{
		m_dwSeed = m_dwSeedTable[Seed];
	}

private:
	static const uint32_t m_dwSeedTable[256];
	static uint32_t m_dwSeed;

	static inline constexpr uint32_t kMagicConstantMul = 69069;
};

template<typename T> requires(std::is_floating_point<T>::value)
T CCstrikeRNG::RandomFloater(uint32_t Seed, T Low, T High)
{
	Seedorize(Seed + Low + High);
	AutoSeedorize();
	AutoSeedorize();

	if (High - Low == 0)
		return Low;

	return (Low + (static_cast<double>(AutoSeedorize() & 0xFFFF) * 0.0000152587890625) * (High - Low));
}

template<typename T> requires(std::is_integral<T>::value)
T CCstrikeRNG::RandomIntegral(uint32_t Seed, T Low, T High)
{
	Seedorize(static_cast<uint32_t>(High + Low + Seed));

	if (High == Low)
		return Low;

	return Low + AutoSeedorize() % (High + Low + 1);
}

uint32_t CCstrikeRNG::m_dwSeed = 0;

// The seed table got from decompiled client.dll binary.
const uint32_t CCstrikeRNG::m_dwSeedTable[256] =
{
	0x00007139, 0x00006A02, 0x00006759, 0x000024EB, 0x00004564, 0x00002A9D, 0x00007076, 0x0000220C,
	0x000018D9, 0x000012F5, 0x00004586, 0x000055D9, 0x00004CBB, 0x000050B6, 0x00002A52, 0x00004E87,
	0x000069BB, 0x00006FDA, 0x000048BF, 0x000064F9, 0x00002180, 0x0000667A, 0x00005D4F, 0x00004734,
	0x00007F4B, 0x000012E4, 0x00000CEA, 0x00000713, 0x00000BDB, 0x00005FEF, 0x000047DF, 0x0000013B,
	0x0000688E, 0x0000038B, 0x00005E26, 0x00003052, 0x000025CA, 0x00000B9C, 0x000028E8, 0x0000406C,
	0x0000589B, 0x00002D09, 0x00006D40, 0x000076C6, 0x0000339D, 0x0000090F, 0x00005C44, 0x000041B7,
	0x0000271D, 0x00005CDC, 0x0000543F, 0x000004E3, 0x00004C7B, 0x00004F59, 0x00004741, 0x000075B2,
	0x000020D2, 0x00005147, 0x00006ADA, 0x00001C01, 0x000052DB, 0x0000438D, 0x00001522, 0x00004B17,
	0x0000280F, 0x000057D0, 0x00006AFC, 0x000026DA, 0x00003D0C, 0x00005F45, 0x0000439C, 0x00000942,
	0x0000253A, 0x00007BC3, 0x00006547, 0x00005C0F, 0x00002DAE, 0x0000671D, 0x00007F5A, 0x00003AB7,
	0x0000474F, 0x000044AE, 0x0000058E, 0x000070A3, 0x00005C37, 0x00003135, 0x0000507A, 0x0000279A,
	0x0000145C, 0x000004E4, 0x0000275A, 0x00005A7E, 0x00004D6F, 0x00007BB3, 0x0000170E, 0x00006036,
	0x00004A04, 0x000037FA, 0x00003A66, 0x000022EB, 0x00005BF4, 0x0000533F, 0x0000579C, 0x00005777,
	0x00000DFF, 0x0000714C, 0x00007722, 0x0000491A, 0x000010B6, 0x00000985, 0x0000579E, 0x00000D6F,
	0x00006E99, 0x00005A79, 0x00006334, 0x0000349F, 0x00004B7C, 0x00003BB7, 0x00000A03, 0x000049D5,
	0x0000332F, 0x000041E3, 0x000025F2, 0x000037F2, 0x00003B5D, 0x00006909, 0x00004BAC, 0x00006681,
	0x00007CB5, 0x00003930, 0x00002CE9, 0x000022ED, 0x00002748, 0x00001933, 0x00006FF0, 0x000029F1,
	0x00003632, 0x000043CC, 0x00002059, 0x00006551, 0x0000067D, 0x000012F2, 0x00001D18, 0x000031C8,
	0x00005542, 0x00001565, 0x000027B7, 0x00004141, 0x00006911, 0x00002287, 0x000078E3, 0x00006D4A,
	0x00006A93, 0x0000606D, 0x00007E2A, 0x00000DC5, 0x0000306E, 0x00007036, 0x00002503, 0x000027E0,
	0x00000269, 0x0000349B, 0x0000570F, 0x00000948, 0x000017D1, 0x000066C8, 0x00000B9E, 0x0000239A,
	0x0000551B, 0x00006D6A, 0x00001275, 0x00003C1B, 0x00000CCA, 0x00002A0A, 0x00007BCF, 0x000043A8,
	0x00004794, 0x00003099, 0x000041A1, 0x00006AF0, 0x000057C0, 0x00001D4C, 0x00001622, 0x000046E0,
	0x00003BD2, 0x00007CAA, 0x00007B8B, 0x0000195F, 0x0000146A, 0x000079E3, 0x0000091B, 0x0000123C,
	0x0000316A, 0x00004763, 0x0000015F, 0x00001C64, 0x00007A57, 0x000075A7, 0x00001DB0, 0x00000B59,
	0x00003602, 0x00002C4F, 0x000032FD, 0x00003CDF, 0x00007567, 0x00007975, 0x000013CB, 0x000002F9,
	0x000025D5, 0x00002B3E, 0x00005379, 0x00006A13, 0x00000E4F, 0x000067AE, 0x00004EC9, 0x00002F81,
	0x00003C33, 0x000076C1, 0x00001D9C, 0x00007C28, 0x00002319, 0x000072B7, 0x000051FD, 0x0000377B,
	0x000073FE, 0x000052AF, 0x00002861, 0x000006AA, 0x00006FA2, 0x00000377, 0x00000D2D, 0x00004C15,
	0x0000382E, 0x000002A3, 0x00001B79, 0x00003B07, 0x0000661A, 0x00002FDC, 0x00007914, 0x000053A1,
	0x0000644E, 0x0000487B, 0x000033C8, 0x00005B14, 0x00005787, 0x00004157, 0x000003DF, 0x00002414,
	0x000014FD, 0x000072DA, 0x000017E5, 0x00003B89, 0x00006C43, 0x00004B5B, 0x00004DB0, 0x00004D87
};
