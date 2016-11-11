#pragma once

#include <string>
#include <vector>

namespace apryx {

	/*
	TJHOS CLASS DUDE IS JUST SO FUCKING WRONG OM MY LORD TTITES MC JIGGLES
	*/

	class Type {
		enum {
			BUILD_IN, CLASS, FUNCTION, 
			
			ERROR
		} m_Type; //Oh yes, a type has a type now!


		//For functions
		std::vector<Type> m_Signatures;

		//For classes
		std::string m_Name;

	public:
		Type();
		~Type();
		
		bool isBuildIn() const;
		bool isClass() const;
		bool isFunction() const;

		//All
		std::string getSignature() const;
		
		//Class
		const std::string &getName() const;
		
		//Function
		int getArgumentCount() const;
		const Type &getArgumentType(int index) const;
		const Type &getReturnType() const;

		static Type getInt();
		static Type getFloat();
		static Type getString();
		static Type getVoid();
		static Type getClass(const std::string cls);

		friend std::ostream& operator<<(std::ostream &o, const Type &type);
		friend bool operator==(const Type &left, const Type &right);
		operator bool();
	};

}