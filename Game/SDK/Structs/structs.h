#pragma once
#include "../../../stdafx.h"

template<class T>
struct TArray
{
	friend struct FString;

public:
	T* Data;
	UINT32 Count;
	UINT32 Max;

	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};


	inline void PushBack(const T& item)
	{
		if (Count >= Max)
		{
			// Increase the size of the array.
			UINT32 newMax = Max == 0 ? 1 : Max * 2;
			T* newData = new T[newMax];

			// Copy existing elements to the new array.
			for (UINT32 i = 0; i < Count; ++i)
			{
				newData[i] = Data[i]; // Ensure i is within the old Max.
			}

			// Safely delete the old array and update pointers and sizes.
			for (UINT32 i = 0; i < Count; ++i) {
				Data[i].~T();
			}

			Data = newData;
			Max = newMax;
		}

		// Ensure Count is within the new Max.
		if (Count < Max)
		{
			Data[Count] = item; // Add the new item.
			Count++;
		}
	}

	inline void Clear()
	{
		if (Data) {
			for (UINT32 i = 0; i < Count; ++i) {
				Data[i].~T();
			}
			// Add your custom memory deallocation logic here instead of delete[].
			Data = nullptr;
			Count = Max = 0;
		}
	}

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}
};

struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	};

	inline FString(const wchar_t* other)
	{
		Max = Count = *other ? My_wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	bool IsEmpty() const
	{
		return Count <= 1;
	}

	inline const wchar_t* c_str() const
	{
		if (Data != nullptr)
			return Data;
		else
			return xor_w(L"");
	}

	void backspace()
	{
		if (this->Count > 0) {
			this->Data[--this->Count] = L'\0';
		}
	}
};

static FString GlobalString;

template<class TEnum>
class TEnumAsByte
{
public:
	inline TEnumAsByte()
	{
	}

	inline TEnumAsByte(TEnum _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(int32_t _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(uint8_t _value)
		: value(_value)
	{
	}

	inline operator TEnum() const
	{
		return (TEnum)value;
	}

	inline TEnum GetValue() const
	{
		return (TEnum)value;
	}

private:
	uint8_t value;
};

class FName {
public:
	FName() : comparison_index(std::uint32_t()), number(std::int32_t()) {};
	FName(std::uint32_t index) : comparison_index(index), number(std::int32_t()) {};

public:
	std::uint32_t comparison_index;
	std::int32_t number;

	inline bool operator==(const FName& other) const
	{
		return comparison_index == other.comparison_index;
	};
};;

class FTextData {
public:
	char pad_0x0000[0x28];  //0x0000
	wchar_t* Name;          //0x0028 
	__int32 Length;         //0x0030 
};

struct FText {
	FTextData* Data;
	char UnknownData[0x10];

	wchar_t* GetText() const {
		if (Data)
			return Data->Name;

		return nullptr;
	}
};

struct FVector
{
	double                                             X;                                                        // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Y;                                                        // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Z;                                                        // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FVector()
		: X(0), Y(0), Z(0)
	{ }

	inline FVector(double x, double y, double z)
		: X(x),
		Y(y),
		Z(z)
	{ }

	bool IsNearlyZero() const {
		const float Tolerance = 1e-6;
		return (X * X + Y * Y + Z * Z) < Tolerance;
	}

	__forceinline FVector operator-(const FVector& V) {
		return FVector(X - V.X, Y - V.Y, Z - V.Z);
	}

	__forceinline FVector operator+(const FVector& V) {
		return FVector(X + V.X, Y + V.Y, Z + V.Z);
	}

	__forceinline FVector operator*(float Scale) const {
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}

	__forceinline FVector operator/(float Scale) const {
		const float RScale = 1.f / Scale;
		return FVector(X * RScale, Y * RScale, Z * RScale);
	}

	__forceinline FVector operator+(float A) const {
		return FVector(X + A, Y + A, Z + A);
	}

	__forceinline FVector operator-(float A) const {
		return FVector(X - A, Y - A, Z - A);
	}

	__forceinline FVector operator*(const FVector& V) const {
		return FVector(X * V.X, Y * V.Y, Z * V.Z);
	}

	__forceinline FVector operator/(const FVector& V) const {
		return FVector(X / V.X, Y / V.Y, Z / V.Z);
	}

	__forceinline float operator|(const FVector& V) const {
		return X * V.X + Y * V.Y + Z * V.Z;
	}

	__forceinline float operator^(const FVector& V) const {
		return X * V.Y - Y * V.X - Z * V.Z;
	}

	__forceinline FVector& operator+=(const FVector& v) {
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}

	__forceinline FVector& operator-=(const FVector& v) {
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}

	__forceinline FVector& operator*=(const FVector& v) {
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;
		return *this;
	}

	__forceinline FVector& operator/=(const FVector& v) {
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;
		return *this;
	}

	__forceinline bool operator==(const FVector& src) const {
		return (src.X == X) && (src.Y == Y) && (src.Z == Z);
	}

	__forceinline bool operator!=(const FVector& src) const {
		return (src.X != X) || (src.Y != Y) || (src.Z != Z);
	}

	__forceinline float SizeSquared() const {
		return X * X + Y * Y + Z * Z;
	}

	__forceinline float SizeSquared2D() const {
		return X * X + Y * Y;
	}

	__forceinline float Dot(const FVector& vOther) const {
		const FVector& a = *this;

		return (a.X * vOther.X + a.Y * vOther.Y + a.Z * vOther.Z);
	}

	__forceinline explicit operator bool() const {
		// Define what it means for an FRotator to be "true".
		// For example, an FRotator could be considered "true" if any of its components are non-zero.
		return X != 0.0 || Y != 0.0 || Z != 0.0;
	}

	/*float Distance(FVector v)
	{
		return ((X - v.X) * (X - v.X) +
			(Y - v.Y) * (Y - v.Y) +
			(Z - v.Z) * (Z - v.Z));
	}*/

	/*double Distance(FVector v)
	{
		return double(LI_FN(sqrt).safe_cached()(LI_FN(pow).safe_cached()(v.X - X, 2.0) + LI_FN(pow).safe_cached()(v.Y - Y, 2.0) + LI_FN(pow).safe_cached()(v.Z - Z, 2.0)));
	}*/

	double Distance(FVector v)
	{
		double dx = v.X - X;
		double dy = v.Y - Y;
		double dz = v.Z - Z;

		double squaredDistance = dx * dx + dy * dy + dz * dz;

		// Approximate the square root using the Newton-Raphson method
		double sqrtDistance = squaredDistance;
		double temp = 0;
		while (sqrtDistance != temp) {
			temp = sqrtDistance;
			sqrtDistance = 0.5 * (sqrtDistance + squaredDistance / sqrtDistance);
		}

		return sqrtDistance;
	}

};

struct FVector2D
{
	double                                             X;                                                        // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Y;                                                        // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FVector2D()
		: X(0), Y(0)
	{ }

	inline FVector2D(double x, double y)
		: X(x),
		Y(y)
	{ }

	__forceinline explicit operator bool() const {
		// Define what it means for an FRotator to be "true".
		// For example, an FRotator could be considered "true" if any of its components are non-zero.
		return X != 0.0 || Y != 0.0;
	}

	__forceinline FVector2D operator-(const FVector2D& V) {
		return FVector2D(X - V.X, Y - V.Y);
	}

	__forceinline FVector2D operator+(const FVector2D& V) {
		return FVector2D(X + V.X, Y + V.Y);
	}

	__forceinline FVector2D operator*(double Scale) const {
		return FVector2D(X * Scale, Y * Scale);
	}

	__forceinline FVector2D operator/(double Scale) const {
		const float RScale = 1.f / Scale;
		return FVector2D(X * RScale, Y * RScale);
	}

	__forceinline FVector2D operator+(double A) const {
		return FVector2D(X + A, Y + A);
	}

	__forceinline FVector2D operator-(double A) const {
		return FVector2D(X - A, Y - A);
	}

	__forceinline FVector2D operator*(const FVector2D& V) const {
		return FVector2D(X * V.X, Y * V.Y);
	}

	__forceinline FVector2D operator/(const FVector2D& V) const {
		return FVector2D(X / V.X, Y / V.Y);
	}

	__forceinline float operator|(const FVector2D& V) const {
		return X * V.X + Y * V.Y;
	}

	__forceinline float operator^(const FVector2D& V) const {
		return X * V.Y - Y * V.X;
	}

	__forceinline FVector2D& operator+=(const FVector2D& v) {
		X += v.X;
		Y += v.Y;
		return *this;
	}

	__forceinline FVector2D& operator-=(const FVector2D& v) {
		X -= v.X;
		Y -= v.Y;
		return *this;
	}

	__forceinline FVector2D& operator*=(const FVector2D& v) {
		X *= v.X;
		Y *= v.Y;
		return *this;
	}

	__forceinline FVector2D& operator/=(const FVector2D& v) {
		X /= v.X;
		Y /= v.Y;
		return *this;
	}

	friend FVector2D operator*(float scalar, const FVector2D& V) {
		return FVector2D(scalar * V.X, scalar * V.Y);
	}

	__forceinline bool operator==(const FVector2D& src) const {
		return (src.X == X) && (src.Y == Y);
	}

	__forceinline bool operator!=(const FVector2D& src) const {
		return (src.X != X) || (src.Y != Y);
	}

	__forceinline float SizeSquared() const {
		return X * X + Y * Y;
	}

	__forceinline float Dot(const FVector2D& vOther) const {
		const FVector2D& a = *this;

		return (a.X * vOther.X + a.Y * vOther.Y);
	}
};

struct alignas(16) FQuat
{
	double                                             X;                                                        // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Y;                                                        // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Z;                                                        // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             W;                                                        // 0x0018(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
};

struct FRotator
{
	double                                             Pitch;                                                    // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Yaw;                                                      // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             Roll;                                                     // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FRotator()
		: Pitch(0), Yaw(0), Roll(0)
	{ }

	inline FRotator(double pitch, double yaw, double roll)
		: Pitch(pitch),
		Yaw(yaw),
		Roll(roll)
	{ }

	__forceinline explicit operator bool() const {
		// Define what it means for an FRotator to be "true".
		// For example, an FRotator could be considered "true" if any of its components are non-zero.
		return Pitch != 0.0 || Yaw != 0.0 || Roll != 0.0;
	}

	__forceinline FRotator operator-(const FRotator& V) {
		return FRotator(Pitch - V.Pitch, Yaw - V.Yaw, Roll - V.Roll);
	}

	__forceinline FRotator operator+(const FRotator& V) {
		return FRotator(Pitch + V.Pitch, Yaw + V.Yaw, Roll + V.Roll);
	}

	__forceinline FRotator operator*(float Scale) const {
		return FRotator(Pitch * Scale, Yaw * Scale, Roll * Scale);
	}

	__forceinline FRotator operator/(float Scale) const {
		const float RScale = 1.f / Scale;
		return FRotator(Pitch * RScale, Yaw * RScale, Roll * RScale);
	}

	__forceinline FRotator operator+(float A) const {
		return FRotator(Pitch + A, Yaw + A, Roll + A);
	}

	__forceinline FRotator operator-(float A) const {
		return FRotator(Pitch - A, Yaw - A, Roll - A);
	}

	__forceinline FRotator operator*(const FRotator& V) const {
		return FRotator(Pitch * V.Pitch, Yaw * V.Yaw, Roll * V.Roll);
	}

	__forceinline FRotator operator/(const FRotator& V) const {
		return FRotator(Pitch / V.Pitch, Yaw / V.Yaw, Roll / V.Roll);
	}

	__forceinline float operator|(const FRotator& V) const {
		return Pitch * V.Pitch + Yaw * V.Yaw + Roll * V.Roll;
	}

	__forceinline float operator^(const FRotator& V) const {
		return Pitch * V.Yaw - Yaw * V.Pitch - Roll * V.Roll;
	}

	__forceinline FRotator& operator+=(const FRotator& v) {
		Pitch += v.Pitch;
		Yaw += v.Yaw;
		Roll += v.Roll;
		return *this;
	}

	__forceinline FRotator& operator-=(const FRotator& v) {
		Pitch -= v.Pitch;
		Yaw -= v.Yaw;
		Roll -= v.Roll;
		return *this;
	}

	__forceinline FRotator& operator*=(const FRotator& v) {
		Pitch *= v.Pitch;
		Yaw *= v.Yaw;
		Roll *= v.Roll;
		return *this;
	}

	__forceinline FRotator& operator/=(const FRotator& v) {
		Pitch /= v.Pitch;
		Yaw /= v.Yaw;
		Roll /= v.Roll;
		return *this;
	}

	__forceinline bool operator==(const FRotator& src) const {
		return (src.Pitch == Pitch) && (src.Yaw == Yaw) && (src.Roll == Roll);
	}

	__forceinline bool operator!=(const FRotator& src) const {
		return (src.Pitch != Pitch) || (src.Yaw != Yaw) || (src.Roll != Roll);
	}

	__forceinline double FMod(double a1, double a2) {
		if (a2 > 0.00000001 || a2 < -0.00000001) {
			double result = a1 - (int)(a1 / a2) * a2;
			return result;
		}
		else {
			return 0.0;
		}
	}

	__forceinline double ClampAxis(double Angle) {
		// returns Angle in the range (-360,360)
		Angle = FMod(Angle, (double)360.f);

		if (Angle < (double)0.f) {
			// shift to [0,360) range
			Angle += (double)360.f;
		}

		return Angle;
	}

	__forceinline double NormalizeAxis(double Angle) {
		// returns Angle in the range [0,360)
		Angle = ClampAxis(Angle);

		if (Angle > (double)180.f) {
			// shift to (-180,180]
			Angle -= (double)360.f;
		}

		return Angle;
	}

	__forceinline double Clamp(double value, double min, double max) {
		if (value < min) {
			return min;
		}
		else if (value > max) {
			return max;
		}
		else {
			return value;
		}
	}

	__forceinline void Normalize() {
		Pitch = NormalizeAxis(Pitch);
		Yaw = NormalizeAxis(Yaw);
		Roll = NormalizeAxis(Roll);
	}

	FVector Euler() const
	{
		return FVector(Pitch, Yaw, Roll);
	}
};

//struct FKey {
//	FName KeyName;
//	unsigned char UnknownData00[0x10];
//
//	// Default constructor
//	FKey() {
//		// Initialize KeyName and UnknownData00 as needed
//		for (int i = 0; i < 0x10; ++i) {
//			UnknownData00[i] = 0;
//		}
//	}
//
//	// Constructor that takes an FName object
//	FKey(const FName& name) : KeyName(name) {
//		// Initialize UnknownData00 with zeros
//		for (int i = 0; i < 0x10; ++i) {
//			UnknownData00[i] = 0;
//		}
//	}
//};

struct FKey
{
	struct FName                                       KeyName;                                                  // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0004(0x0014) MISSED OFFSET

	friend bool operator==(const FKey& a, const FKey& b) {
		return a.KeyName == b.KeyName;  // Utilize the existing FName == operator
	}

	// Optionally, define inequality operator for FKey
	friend bool operator!=(const FKey& a, const FKey& b) {
		return !(a == b);
	}
};

enum class EDrawDebugTrace : uint8_t
{
	None = 0,
	ForOneFrame = 1,
	ForDuration = 2,
	Persistent = 3,
	EDrawDebugTrace_MAX = 4
};

struct FLinearColor
{
	float                                              R;                                                        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              G;                                                        // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              B;                                                        // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              A;                                                        // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FLinearColor()
		: R(0), G(0), B(0), A(0)
	{ }

	inline FLinearColor(float r, float g, float b, float a = 1)
		: R(r / 255.0f),
		G(g / 255.0f),
		B(b / 255.0f),
		A(a)
	{ }

};

struct SpecialStruct
{
	struct FString name;
	struct FLinearColor color;
};

enum class EBlendMode : uint8_t
{
	BLEND_Opaque = 0,
	BLEND_Masked = 1,
	BLEND_Translucent = 2,
	BLEND_Additive = 3,
	BLEND_Modulate = 4,
	BLEND_AlphaComposite = 5,
	BLEND_AlphaHoldout = 6,
	BLEND_MAX = 7
};

enum class EFortItemType : uint8_t
{
	WorldItem = 0,
	Ammo = 1,
	Badge = 2,
	BackpackPickup = 3,
	BuildingPiece = 4,
	CharacterPart = 5,
	Consumable = 6,
	Deco = 7,
	EditTool = 8,
	Ingredient = 9,
	ItemCache = 10,
	Food = 11,
	Gadget = 12,
	AthenaGadget = 13,
	HomebaseGadget = 14,
	BattleLabDevice = 15,
	SpyTechPerk = 16,
	HeroAbility = 17,
	MissionItem = 18,
	Trap = 19,
	MultiItem = 20,
	Weapon = 21,
	WeaponMelee = 22,
	WeaponRanged = 23,
	WeaponHarvest = 24,
	WeaponCreativePhone = 25,
	WeaponMod = 26,
	WorldResource = 27,
	CreativeUserPrefab = 28,
	CreativePlayset = 29,
	Vehicle = 30,
	Npc = 31,
	PlayerAugment = 32,
	AccountItem = 33,
	AccountResource = 34,
	CollectedResource = 35,
	Alteration = 36,
	CardPack = 37,
	Currency = 38,
	Hero = 39,
	Schematic = 40,
	Worker = 41,
	TeamPerk = 42,
	PlayerTech = 43,
	Token = 44,
	DailyRewardScheduleToken = 45,
	CodeToken = 46,
	Stat = 47,
	Buff = 48,
	BuffCredit = 49,
	Quest = 50,
	Accolades = 51,
	FriendChest = 52,
	MedalsPunchCard = 53,
	RepeatableDailiesCard = 54,
	ChallengeBundle = 55,
	ChallengeBundleSchedule = 56,
	ChallengeBundleCompletionToken = 57,
	GameplayModifier = 58,
	Outpost = 59,
	HomebaseNode = 60,
	Defender = 61,
	ConversionControl = 62,
	DeployableBaseCloudSave = 63,
	ConsumableAccountItem = 64,
	Quota = 65,
	Expedition = 66,
	HomebaseBannerIcon = 67,
	HomebaseBannerColor = 68,
	AthenaSkyDiveContrail = 69,
	PersonalVehicle = 70,
	AthenaGlider = 71,
	AthenaPickaxe = 72,
	AthenaHat = 73,
	AthenaBackpack = 74,
	AthenaCharacter = 75,
	AthenaDance = 76,
	AthenaConsumableEmote = 77,
	AthenaLoadingScreen = 78,
	AthenaBattleBus = 79,
	AthenaVehicleCosmetic = 80,
	AthenaItemWrap = 81,
	AthenaCallingCard = 82,
	AthenaMapMarker = 83,
	AthenaMusicPack = 84,
	AthenaPetCosmetic = 85,
	AthenaCharmCosmetic = 86,
	AthenaVictoryPose = 87,
	AthenaSeasonTreasure = 88,
	AthenaSeason = 89,
	AthenaRewardGraph = 90,
	AthenaExtResource = 91,
	EventDescription = 92,
	BattleLabDeviceAccount = 93,
	AthenaEventToken = 94,
	EventPurchaseTracker = 95,
	CosmeticVariantToken = 96,
	CampaignHeroLoadout = 97,
	Playset = 98,
	PrerollData = 99,
	CreativePlot = 100,
	PlayerSurveyToken = 101,
	CosmeticLocker = 102,
	BannerToken = 103,
	RestedXpBoosterToken = 104,
	RewardEventGraphPurchaseToken = 105,
	HardcoreModifier = 106,
	EventDependentItem = 107,
	ItemAccessToken = 108,
	STWAccoladeReward = 109,
	Campsite = 110,
	VictoryCrown = 111,
	RealitySapling = 112,
	Apparel = 113,
	ApparelLayout = 114,
	PlayerAugmentsPersistence = 115,
	SpecialItem = 116,
	Emote = 117,
	Stack = 118,
	CollectionBookPage = 119,
	BGAConsumableWrapper = 120,
	GiftBox = 121,
	GiftBoxUnlock = 122,
	PlaysetProp = 123,
	RegCosmeticDef = 124,
	Profile = 125,
	Max_None = 126,
	EFortItemType_MAX = 127
};

enum class EFortItemTier : uint8_t
{
	No_Tier = 0,
	I = 1,
	II = 2,
	III = 3,
	IV = 4,
	V = 5,
	VI = 6,
	VII = 7,
	VIII = 8,
	IX = 9,
	X = 10,
	NumItemTierValues = 11,
	EFortItemTier_MAX = 12
};

struct FFortColorPalette {
	struct FLinearColor Color1; // 0x00(0x10)
	struct FLinearColor Color2; // 0x10(0x10)
	struct FLinearColor Color3; // 0x20(0x10)
	struct FLinearColor Color4; // 0x30(0x10)
	struct FLinearColor Color5; // 0x40(0x10)
};

enum class ETraceTypeQuery : uint8_t
{
	TraceTypeQuery1 = 0,
	TraceTypeQuery2 = 1,
	TraceTypeQuery3 = 2,
	TraceTypeQuery4 = 3,
	TraceTypeQuery5 = 4,
	TraceTypeQuery6 = 5,
	TraceTypeQuery7 = 6,
	TraceTypeQuery8 = 7,
	TraceTypeQuery9 = 8,
	TraceTypeQuery10 = 9,
	TraceTypeQuery11 = 10,
	TraceTypeQuery12 = 11,
	TraceTypeQuery13 = 12,
	TraceTypeQuery14 = 13,
	TraceTypeQuery15 = 14,
	TraceTypeQuery16 = 15,
	TraceTypeQuery17 = 16,
	TraceTypeQuery18 = 17,
	TraceTypeQuery19 = 18,
	TraceTypeQuery20 = 19,
	TraceTypeQuery21 = 20,
	TraceTypeQuery22 = 21,
	TraceTypeQuery23 = 22,
	TraceTypeQuery24 = 23,
	TraceTypeQuery25 = 24,
	TraceTypeQuery26 = 25,
	TraceTypeQuery27 = 26,
	TraceTypeQuery28 = 27,
	TraceTypeQuery29 = 28,
	TraceTypeQuery30 = 29,
	TraceTypeQuery31 = 30,
	TraceTypeQuery32 = 31,
	TraceTypeQuery_MAX = 32,
	ETraceTypeQuery_MAX = 33
};

struct FHitResult {
	unsigned char UnknownData69[0x4]; // 0x00(0x04)
	int32_t FaceIndex; // 0x04(0x04)
	float Time; // 0x08(0x04)
	float Distance; // 0x0c(0x04)
	char pad_C[0x4]; // 0x10(0x04)
	struct FVector Location; // 0x14(0x18)
	struct FVector ImpactPoint; // 0x2c(0x18)
	struct FVector Normal; // 0x44(0x18)
	struct FVector ImpactNormal; // 0x5c(0x18)
	struct FVector TraceStart; // 0x74(0x18)
	struct FVector TraceEnd; // 0x8c(0x18)
	float PenetrationDepth; // 0xa4(0x04)
	int32_t MyItem; // 0xa8(0x04)
	int32_t Item; // 0xac(0x04)
	char ElementIndex; // 0xb0(0x01)
	char bBlockingHit : 1; // 0xb1(0x01)
	char bStartPenetrating : 1; // 0xb1(0x01)
	char pad_B1_2 : 6; // 0xb1(0x01)
	char pad_B2[0x2]; // 0xb2(0x02)
	void* PhysMaterial; // 0xb4(0x08)
	void* HitObjectHandle; // 0xbc(0x20)
	void* Component; // 0xdc(0x08)
	char pad_E4[0xC]; // 0xe4(0x0c)
	struct FName BoneName; // 0xf0(0x04)
	struct FName MyBoneName; // 0xf4(0x04)
};

struct Camera_Struct
{
	FVector Location;
	FRotator Rotation;
	float FieldOfView;
};

struct WeaponData {
	float Speed;
	float Gravity;
};

struct ReticlePair
{
	unsigned short TableValue;
	unsigned short TableOffset;
};

enum class EMaterialParameterAssociation : uint8_t {
	LayerParameter = 0,
	BlendParameter = 1,
	GlobalParameter = 2,
	EMaterialParameterAssociation_MAX = 3
};
struct FMaterialParameterInfo {
	struct FName Name; // 0x00(0x04)
	EMaterialParameterAssociation Association; // 0x04(0x01)
	char pad_5[0x3]; // 0x05(0x03)
	int32_t Index; // 0x08(0x04)
};
struct FVectorParameterValue {
	struct FMaterialParameterInfo ParameterInfo; // 0x00(0x0c)
	struct FLinearColor ParameterValue; // 0x0c(0x10)
};
struct FTextureParameterValue {
	struct FMaterialParameterInfo ParameterInfo; // 0x00(0x0c)
	char pad_C[0x4]; // 0x0c(0x04)
	struct UTexture* ParameterValue; // 0x10(0x08)
	//struct FGuid ExpressionGUID; // 0x18(0x10)
};

struct FScalableFloat {
	float Value; // 0x00(0x04)
	char pad_18[0x24];
};

enum class EMouseCaptureMode : uint8_t {
	NoCapture = 0,
	CapturePermanently = 1,
	CapturePermanently_IncludingInitialMouseDown = 2,
	CaptureDuringMouseDown = 3,
	CaptureDuringRightMouseDown = 4,
	EMouseCaptureMode_MAX = 5
};

enum class EFortWeaponCoreAnimation : uint8_t
{
	Melee = 0,
	Pistol = 1,
	Shotgun = 2,
	PaperBlueprint = 3,
	Rifle = 4,
	MeleeOneHand = 5,
	MachinePistol = 6,
	RocketLauncher = 7,
	GrenadeLauncher = 8,
	GoingCommando = 9,
	AssaultRifle = 10,
	TacticalShotgun = 11,
	SniperRifle = 12,
	TrapPlacement = 13,
	ShoulderLauncher = 14,
	AbilityDecoTool = 15,
	Crossbow = 16,
	C4 = 17,
	RemoteControl = 18,
	DualWield = 19,
	AR_BullPup = 20,
	AR_ForwardGrip = 21,
	MedPackPaddles = 22,
	SMG_P90 = 23,
	AR_DrumGun = 24,
	Consumable_Small = 25,
	Consumable_Large = 26,
	Balloon = 27,
	MountedTurret = 28,
	CreativeTool = 29,
	ExplosiveBow = 30,
	AshtonIndigo = 31,
	AshtonChicago = 32,
	MeleeDualWield = 33,
	Unarmed = 34,
	MAX = 35,
};

// Enum FortniteGame.EFortCustomPartType
enum class EFortCustomPartType : uint8_t {
	Head = 0,
	Body = 1,
	Hat = 2,
	Backpack = 3,
	MiscOrTail = 4,
	Face = 5,
	Gameplay = 6,
	NumTypes = 7,
	EFortCustomPartType_MAX = 8
};
enum class EFortCustomGender : uint8_t {
	Invalid = 0,
	Male = 1,
	Female = 2,
	Both = 3,
	EFortCustomGender_MAX = 4
};

////////// NEW SHIT
class TUObjectArray
{
public:

	enum
	{
		ElementsPerChunk = 0x10000,
	};

	struct FUObjectItem
	{
		class UObject* Object;
		uint8_t Pad[0x10];
	};

	FUObjectItem** Objects;
	uint8_t Pad_0[0x08];
	uint32_t MaxElements;
	uint32_t NumElements;
	uint32_t MaxChunks;
	uint32_t NumChunks;

	inline uint32_t Num() const
	{
		return NumElements;
	}

	inline class UObject* GetByIndex(const uint32_t Index) const
	{
		if (Index < 0 || Index > NumElements)
			return nullptr;

		const uint32_t ChunkIndex = Index / ElementsPerChunk;
		const uint32_t InChunkIdx = Index % ElementsPerChunk;

		return Objects[ChunkIndex][InChunkIdx].Object;
	}
};

class UObject
{
public:
	inline static TUObjectArray* GObjects = nullptr;
	void* VTable;
	uint32_t Flags;
	uint32_t Index;
	class UClass* Class;
	class FName Name;
	uint8_t Pad_38[0x4];
	class UObject* Outer;
};

class FWeakObjectPtr
{
public:
	uint32_t                                         ObjectIndex;                                       // 0x0000(0x0004)(NOT AUTO-GENERATED PROPERTY)
	uint32_t                                         ObjectSerialNumber;                                // 0x0004(0x0004)(NOT AUTO-GENERATED PROPERTY)

public:
	class UObject* Get();
	class UObject* operator->() const;
	bool operator==(const FWeakObjectPtr& Other) const;
	bool operator!=(const FWeakObjectPtr& Other) const;
	bool operator==(const class UObject* Other) const;
	bool operator!=(const class UObject* Other) const;
};

inline UObject* FWeakObjectPtr::Get()
{
	return UObject::GObjects->GetByIndex(ObjectIndex);
}
inline UObject* FWeakObjectPtr::operator->() const
{
	return UObject::GObjects->GetByIndex(ObjectIndex);
}

template<typename TObjectID>
class TPersistentObjectPtr
{
public:
	FWeakObjectPtr                                WeakPtr;                                           // 0x0000(0x0008)(NOT AUTO-GENERATED PROPERTY)
	TObjectID                                     ObjectID;                                          // 0x0008(0x0000)(NOT AUTO-GENERATED PROPERTY)

public:
	class UObject* Get()
	{
		return WeakPtr.Get();
	}
	class UObject* operator->() const
	{
		return WeakPtr.Get();
	}
};

struct FSoftObjectPath
{
public:

	FName AssetPathName;


	FString SubPathString;
};

class FSoftObjectPtr : public TPersistentObjectPtr<FSoftObjectPath>
{
};

template<typename UEType>
class TSoftObjectPtr : public FSoftObjectPtr
{
public:
	UEType* Get()
	{
		return static_cast<UEType*>(TPersistentObjectPtr::Get());
	}
	UEType* operator->() const
	{
		return static_cast<UEType*>(TPersistentObjectPtr::Get());
	}
};