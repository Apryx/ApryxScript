package ast;

public abstract class Type {

	public static final Type TYPE_OBJECT = new ClassType("Object");
	public static final Type TYPE_STRING = new ClassType("String");

	public static final Type UNKNOWN = new BuiltInType("?");
	public static final Type VOID = new BuiltInType("void");
	
	public static final Type INT = new BuiltInType("int");
	public static final Type FLOAT = new BuiltInType("float");
	public static final Type DOUBLE = new BuiltInType("double");
	
	private String name;
	
	public Type(String name){
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	/**
	 * If its an invokeable function
	 * @return
	 */
	public abstract boolean isInvokeable();
	
	@Override
	public String toString() {
		return name;
	}
	
}
