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
		std::string m_Namespace;

	public:
		Type();
		~Type();
		
		bool isBuildIn() const;
		bool isClass() const;
		bool isFunction() const;

		//All
		std::string getSignature() const;
		
		//Class
		const std::string &getNamespace() const;
		const std::string &getName() const;
		
		//Function
		int getArgumentCount() const;
		const Type &getArgumentType(int index) const;
		const Type &getReturnType() const;

		static Type getInt();
		static Type getFloat();
		static Type getClass(const std::string cls, const std::string nmspc);

		friend bool operator==(const Type &left, const Type &right);
		operator bool();
	};

}