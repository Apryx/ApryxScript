package ast;

public class Variable {
	
	private String name, type;
	private boolean argument;

	public Variable(String name, String type){
		this(name, type, false);
	}
	
	public Variable(String name, String type, boolean argument){
		this.name = name;
		this.type = type;
		this.argument = argument;
	}
	
	public String getType() {
		return type;
	}
	
	public String getName() {
		return name;
	}
	
	public boolean isArgument() {
		return argument;
	}
	
	public String toXML(){
		return String.format("<%s name=\"%s\" type=\"%s\" />", argument ? "argument" : "variable", name, type);
	}
}
