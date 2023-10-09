#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed{
private:
	const static int bits = 8;
	int	number;
public:
	Fixed();
	Fixed(const Fixed &obj);
	Fixed(int num);
	Fixed(const float num);
	Fixed& operator=(const Fixed &obj);
	float toFloat( void ) const;
	int toInt( void ) const;
	~Fixed();
	int getRawBits(void) const;
	void setRawBits(int const raw);
};
std::ostream &operator<<(std::ostream &out, const Fixed &obj);
# endif