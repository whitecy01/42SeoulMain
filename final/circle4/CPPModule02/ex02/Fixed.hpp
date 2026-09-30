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

	bool operator>(Fixed const &obj) const;
	bool operator<(Fixed const &obj) const;
	bool operator>=(Fixed const &obj) const;
	bool operator<=(Fixed const &obj) const;
	bool operator==(Fixed const &obj) const;
	bool operator!=(Fixed const &obj) const;

	Fixed operator+ (const Fixed &obj);
	Fixed operator- (const Fixed &obj);
	Fixed operator* (const Fixed &obj);
	Fixed operator/ (const Fixed &obj);

	Fixed	&operator++(void);
	const Fixed	operator++(int);
	Fixed	&operator--(void);
	const Fixed	operator--(int);

	static Fixed	&min(Fixed &left, Fixed &right);
	static const Fixed	&min(Fixed const &left, Fixed const &right);
	static Fixed	&max(Fixed &left, Fixed &right);
	static const Fixed	&max(Fixed const &left, Fixed const &right);

};
std::ostream &operator<<(std::ostream &out, const Fixed &obj);
# endif