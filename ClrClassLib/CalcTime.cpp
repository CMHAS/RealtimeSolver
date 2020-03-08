#include "CalcTime.h"
#include <future>
#include <vector>

namespace CppNative {
	using std::vector;
	using std::pair;

	double CalcTime::Get(eVALUE val) const
	{
		double ret(0.0);
		switch (val)
		{
		case eVALUE::DIST:		ret = m_dist;		break;
		case eVALUE::ACC:		ret = m_acc;		break;
		case eVALUE::RET:		ret = m_ret;		break;
		case eVALUE::V_START:	ret = m_vel.at(0);	break;
		case eVALUE::V_CRUISE:	ret = m_vel.at(1);	break;
		case eVALUE::V_END:		ret = m_vel.at(2);	break;
		default:				ret = 0.0;			break;
		}
		return ret;
	}

	/* Return: A vector with pairs of time and velocity */
	vector<pair<double, double>> CalcTime::totTime(const pair<eVALUE, double>& calcVar)
	{
		
		if ((calcVar.first == eVALUE::ACC) || (calcVar.first == eVALUE::RET) || (calcVar.first == eVALUE::V_CRUISE)) {
			if (std::fabs(calcVar.second) < std::numeric_limits<double>::epsilon())
				return vector<pair<double, double>>({ {0.0, 0.0}, {0.0, 0.0} });
		}

		/* Calc new time with a new value */
		switch (calcVar.first)
		{
		case eVALUE::DIST:		m_dist		= calcVar.second; break;
		case eVALUE::ACC:		m_acc		= calcVar.second; break;
		case eVALUE::RET:		m_ret		= calcVar.second; break;
		case eVALUE::V_START:	m_vel.at(0) = calcVar.second; break;
		case eVALUE::V_CRUISE:	m_vel.at(1) = calcVar.second; break;
		case eVALUE::V_END:		m_vel.at(2) = calcVar.second; break;
		default:											  break;
		}
		return this->calcVector();
	}

	vector<pair<double, double>> CalcTime::totTime(cdbl dist, cdbl acc, cdbl ret, cdbl v0, cdbl v1, cdbl v2)
	{
		if (isLessThenAbsEpsInArr<double, 3UL>({ acc, ret, v1 })) {
			return vector<pair<double, double>>({ {0.0, 0.0}, {0.0, 0.0} });
		}

		m_dist		= dist;
		m_acc		= acc;
		m_ret		= ret;
		m_vel.at(0) = v0;
		m_vel.at(1) = v1;
		m_vel.at(2) = v2;
		return this->calcVector();
	}

	vector<pair<double, double>> CalcTime::calcVector() const
	{
		vector<pair<double, double>> timeVelocity(4, { 0.0, m_vel.at(0) });
		const double time(calcTimeCru());

		if (time > 0.0) {
			timeVelocity.at(1) = { calcTime(m_vel.at(0), m_vel.at(1)), m_vel.at(1) };
			timeVelocity.at(2) = { timeVelocity.at(1).first + time, m_vel.at(1) };
			timeVelocity.at(3) = { timeVelocity.at(2).first + calcTime(m_vel.at(1), m_vel.at(2)), m_vel.at(2) };
		}
		else {
			const double tempVel(calcMaxVel());
			if (inRange(m_vel.at(0), tempVel, m_vel.at(2))) {
				timeVelocity.resize(2);
				timeVelocity.at(1) = { calcTime(m_vel.at(0), m_vel.at(2)), m_vel.at(2) };

			}
			else {
				timeVelocity.resize(3);
				timeVelocity.at(1) = { calcTime(m_vel.at(0), tempVel), tempVel };
				timeVelocity.at(2) = { timeVelocity.at(1).first + calcTime(tempVel, m_vel.at(2)), m_vel.at(2) };
			}
		}
		return timeVelocity;
	}

	/* Calculate acceleration or retardation time
	 * Return: Time									*/
	double CalcTime::calcTime(cdbl v0, cdbl v1) const noexcept
	{
		return v0 > v1 ? (v1 - v0) / m_ret : (v1 - v0) / m_acc;
	}

	/* Calculate the crusie time
	 * Return: A negative value will indicate no time to cruise. */
	double CalcTime::calcTimeCru() const
	{
		auto func = [this](cdbl v0, cdbl v1)->double {
			const double diffVelPow(std::pow(v1, 2.0) - std::pow(v0, 2.0));
			return v0 > v1 ? diffVelPow / m_ret : diffVelPow / m_acc;
		};
		std::future<double> fut1 = std::async(std::launch::async, func, m_vel.at(0), m_vel.at(1));
		std::future<double> fut2 = std::async(std::launch::async, func, m_vel.at(1), m_vel.at(2));
		return  (m_dist - 0.5 * (fut1.get() + fut2.get())) / m_vel.at(1);
	}

	/* Calculate max velocity. */
	double CalcTime::calcMaxVel() const
	{
		auto func = [this](cdbl a0, cdbl a1)->double {
			return sqrt((2.0 * a0 * a1 * m_dist + a1 * std::pow(m_vel.at(0), 2.0) - a0 * std::pow(m_vel.at(2), 2.0)) / (a1 - a0));
		};
		return m_vel.at(0) < m_vel.at(1) ? func(m_acc, m_ret) : func(m_ret, m_acc);
	}
}