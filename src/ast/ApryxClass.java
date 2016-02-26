package ast;

import statement.CodeBlock;

public class ApryxClass {
	
	private String name;
	private CodeBlock code;
	
	public ApryxClass(String name, CodeBlock code){
		this.name = name;
		
		this.code = code;
	}
	
	public String getName() {
		return name;
	}
	
	public CodeBlock getCode() {
		return code;
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		builder.append("<class name=\"");
		builder.append(name);
		
		builder.append("\">");
		
		builder.append(code.toXML());
		
		builder.append("</class>");
		
		return builder.toString();
	}
}
