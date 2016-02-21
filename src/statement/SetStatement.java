package statement;

public class SetStatement extends Statement {
	
	private String name;
	private Expression value;
	
	public SetStatement(String name, Expression value){
		this.name = name;
		this.value = value;
	}
	
	public String getName() {
		return name;
	}
	
	public Expression getValue() {
		return value;
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		/*<set name="a" type="void">
			<constant type="int">0</constant>
		</set>*/
		
		builder.append("<set name=\"");
		builder.append(name);
		builder.append("\" type=\"");
		builder.append(value.getType());
		builder.append("\">");
		
		builder.append(value.toXML());
		
		builder.append("</set>");
		
		return builder.toString();
	}
}
