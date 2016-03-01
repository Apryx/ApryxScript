package ast;

public class NameAndType {
	private String name;
	private Type type;
	
	public NameAndType(String name, Type type){
		this.name = name;
		this.type = type;
	}
	
	public Type getType() {
		return type;
	}
	
	public String getName() {
		return name;
	}
	
	@Override
	public String toString() {
		return name + ":" + type;
	}
	
}
