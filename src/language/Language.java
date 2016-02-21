package language;

public class Language {

	public static final String VAR = "var";
	public static final String CLASS = "class";
	public static final String FUNCTION = "function";

	public static final String TYPE_OBJECT = "Object";
	public static final String TYPE_STRING = "String";
	
	public static final String TYPE_UNKNOWN = "?";
	
	public static final String TYPE_INT = "int";
	public static final String TYPE_FLOAT = "float";
	public static final String TYPE_DOUBLE = "double";
	
	public static boolean isAlphabetic(char c){
		return Character.isAlphabetic(c);
	}
	
	public static boolean isDigit(char c){
		return Character.isDigit(c);
	}
	
	public static boolean isSeperator(char c){
		return c == ',';
	}
	
	public static boolean isMulDiv(char c){
		return c == '*' || c == '/';
	}
	
	public static boolean isPlusMin(char c){
		return c == '+' || c == '-';
	}
	
	public static boolean isKeyword(String word){
		return word.equals(VAR)
				|| word.equals(CLASS)
				|| word.equals(FUNCTION);
	}
	
	public static boolean isWhitespace(char c) {
		return Character.isWhitespace(c);
	}

	public static boolean isString(char c){
		return c == '"';
	}

	public static boolean isColon(char c){
		return c == ':';
	}
	
	public static boolean isBracketOpen(char c){
		return c == '(';
	}

	public static boolean isBracketClose(char c){
		return c == ')';
	}

	public static boolean isCurlyOpen(char c){
		return c == '{';
	}

	public static boolean isCurlyClose(char c){
		return c == '}';
	}
	
	public static boolean isLineEnd(char c){
		return c == ';';
	}
	
	public static boolean isEquals(char c){
		return c == '=';
	}
}
