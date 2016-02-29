package ast;

import statement.CodeBlock;

public class ApryxClass extends CodeBlock{
	
	private String name;
	private Type type;
	
	public ApryxClass(String name){
		super();
		this.name = name;
		type = new ClassType(this);
	}
	
	public String getName() {
		return name;
	}
	
	public Type getType() {
		return type;
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		builder.append("<class name=\"");
		builder.append(name);
		
		builder.append("\">");
		
		builder.append(super.toXML());
		
		builder.append("</class>");
		
		return builder.toString();
	}
}
