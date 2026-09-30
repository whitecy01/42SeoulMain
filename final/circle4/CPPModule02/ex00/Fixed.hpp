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
	Fixed& operator=(const Fixed &obj);
	~Fixed();
	int getRawBits(void) const;
	void setRawBits(int const raw);
};

# endif