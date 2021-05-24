#ifndef LionX_LionX_Base_Time_H
#define LionX_LionX_Base_Time_H

#include "LionX.h"

//===========================================================================================
//	時間類。
//===========================================================================================

namespace LionX
{
	class CTime
	{
	public:
		//	平年天數。
		static const double NormYearDays;
		//	閏年天數。
		static const double LeapYearDays;
		//	平年月總天數。
		static const double NormMonthDays[];
		//	閏年月總天數。
		static const double LeapMonthDays[];
		//	每周的秒數。
		static const double WeekSecond;
		//	每天的秒數。
		static const double DaySecond;
		//	每小時的秒數。
		static const double HourSecond;
		//	每分鐘秒數。
		static const double MinSecond;
		//	微秒單位。
		static const double Microseconds;
	public:
		//	取得當前時間。
		static double Gettimeofday ();
	public:
		inline CTime (double second)
			: mSecond (second) { }
		inline CTime (bool now = false) { mSecond = (now) ? Gettimeofday () : 0.0; }
		//	更新到當前時間。
		inline void Update () { mSecond = Gettimeofday (); }
		//	更新到當前時間。
		inline void AtomUpdate () { double n = Gettimeofday (); Atomic::LockedExchange ((Int64*)&mSecond, *((Int64*)(&n))); }
		//	設定時間。
		inline void Set (double sec) { mSecond = sec; }
		inline void Set (Int32 sec, Int32 ms) { mSecond = (double)sec + (((double)ms) * Microseconds); }
		//	&。
		inline operator double& () { return mSecond; }
		inline operator double () const { return mSecond; }
		//	比較。
		inline friend bool operator == (const CTime& t1, double t2) { return (abs (t1 - t2) < Microseconds); }
		inline friend bool operator == (double t1, const CTime& t2) { return (abs (t1 - t2) < Microseconds); }
		inline friend bool operator == (const CTime& t1, const CTime& t2) { return (abs (t1 - t2) < Microseconds); }
		//	獲取時間。
		inline Int64 GetRealTime () const { return (Int64)(mSecond * 1000000.0); }
		//	取得秒。
		inline Int32 GetSecond () const { return (Int32)mSecond; }
	private:
		double mSecond;
	};
};

#endif //	LionX_LionX_Base_Time_H
