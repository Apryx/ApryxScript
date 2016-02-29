package ast;

public abstract class Type {

	public static final Type OBJECT = new ClassType(new NativeApryxClass("Object", "java.lang.Object"));
	public static final Type STRING = new ClassType(new NativeApryxClass("String", "java.lang.String"));

	public static final Type UNKNOWN = new BuiltInType("?");
	public static final Type UNDEFINED = new BuiltInType("??");
	
	public static final Type VOID = new BuiltInType("void");
	
	public static final Type INT = new BuiltInType("int");
	public static final Type FLOAT = new BuiltInType("float");
	public static final Type DOUBLE = new BuiltInType("double");
	
	public static final Type[] DEFAULT_TYPES = {VOID, INT, FLOAT, DOUBLE, OBJECT, STRING};
	
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
	public abstract ApryxClass getApryxClass();
	
	@Override
	public String toString() {
		return name;
	}
	
}
