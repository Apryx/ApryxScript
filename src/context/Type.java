package context;

public class Type {

	public static final Type STRING = new Type("String");
	public static final Type INTEGER = new Type("int");
	public static final Type FLOAT = new Type("float");
	public static final Type DOUBLE = new Type("double");
	
	public static final Type UNKNOWN = new Type("__unknown__");
	
	private String name;

	public Type(String name){
		this.name = name;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Type other = (Type) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}
	
	
}
