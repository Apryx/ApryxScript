package ast;

import statement.Context;


public class ApryxClass extends Type{
	
	private Context body;
	
	public ApryxClass(String name){
		super(name);
		body = new Context();
	}
	
	public Context getBody() {
		return body;
	}
	
	public void setBody(Context body) {
		this.body = body;
	}
	
	public void typeCheck(){
		getBody().typeCheck();
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		builder.append("<class name=\"");
		builder.append(getName());
		
		builder.append("\">");
		
		//TODO fix
		builder.append(body.toXML());
		
		builder.append("</class>");
		
		return builder.toString();
	}
}
