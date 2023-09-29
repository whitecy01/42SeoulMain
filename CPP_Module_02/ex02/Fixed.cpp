#include "Fixed.hpp"

Fixed::Fixed(void)
{
	this->number = 0;
}

Fixed::Fixed(const Fixed &obj)
{
	*this = obj;
}

Fixed::Fixed(int num)
{
	this->number = num << this->bits;
}

Fixed::Fixed(const float num)
{
	this->number = roundf(num * (1 << this->bits));
}

float Fixed::toFloat(void) const 
{
	return ((float)this->number / (1 << this->bits)); 
}

int Fixed::toInt(void) const 
{
	return (this->number >> this->bits);
}

std::ostream &operator<<(std::ostream &out, const Fixed &obj)
{
	out << obj.toFloat();
	return (out);
}


Fixed& Fixed::operator=(const Fixed &obj)
{
	if (this == &obj)
		return *this;
	this->number = obj.getRawBits();
	return *this;
}

Fixed::~Fixed(void)
{
}

int	Fixed::getRawBits(void) const
{
	return (this->number);
}

void	Fixed::setRawBits(int const raw)
{
	this->number = raw;
}

bool Fixed::operator>(Fixed const &obj) const
{
	return (this->getRawBits() > obj.getRawBits());
}

bool Fixed::operator<(Fixed const &obj) const
{
	return (this->getRawBits() < obj.getRawBits());
}

bool Fixed::operator>=(Fixed const &obj) const
{
	return (this->getRawBits() >= obj.getRawBits());
}

bool Fixed::operator<=(Fixed const &obj) const
{
	return (this->getRawBits() <= obj.getRawBits());
}

bool Fixed::operator==(Fixed const &obj) const
{
	return (this->getRawBits() == obj.getRawBits());
}

bool Fixed::operator!=(Fixed const &obj) const
{
	return (this->getRawBits() != obj.getRawBits());
}

Fixed Fixed::operator+ (const Fixed &obj)
{
	return Fixed(this->toFloat() + obj.toFloat());
}

Fixed Fixed::operator- (const Fixed &obj)
{
	return Fixed(this->toFloat() - obj.toFloat());
}

Fixed Fixed::operator* (const Fixed &obj)
{
	return Fixed(this->toFloat() * obj.toFloat());
}

Fixed Fixed::operator/ (const Fixed &obj)
{
	return Fixed(this->toFloat() / obj.toFloat());
}

Fixed&	Fixed::operator++(void)
{
	this->number++;
	return (*this);
}

const Fixed	Fixed::operator++(int)
{
	const Fixed	fixed(*this);

	this->number++;
	return (fixed);
}

Fixed&	Fixed::operator--(void)
{
	this->number--;
	return (*this);
}

const Fixed	Fixed::operator--(int)
{
	const Fixed	fixed(*this);

	this->number--;
	return (fixed);
}

Fixed&	Fixed::min(Fixed &left, Fixed &right)
{
	if (left <= right)
		return left;
	else
		return right;
}

const Fixed& Fixed::min(Fixed const &left, Fixed const &right)
{
	if (left <= right)
		return left;
	else
		return right;
}

Fixed&	Fixed::max(Fixed &left, Fixed &right)
{
	if (left >= right)
		return left;
	else
		return right;
}

const Fixed& Fixed::max(Fixed const &left, Fixed const &right)
{
	if (left >= right)
		return left;
	else
		return right;
}