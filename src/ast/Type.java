package ast;

public abstract class Type {

	public static final Type OBJECT = new NativeApryxClass("Object", "java.lang.Object");
	public static final Type STRING = new NativeApryxClass("String", "java.lang.String");

	public static final Type UNKNOWN = new UnknownType("unknown");
	public static final Type UNDEFINED = new UnknownType("undefined");
	
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
	
	public boolean isUnknown(){
		return false;
	}
	
	@Override
	public String toString() {
		return name;
	}
	
	public static Type getBuildInType(String name){
		for(Type t : DEFAULT_TYPES){
			if(t.getName().equals(name))
				return t;
		}
		
		return null;
	}
	
}
