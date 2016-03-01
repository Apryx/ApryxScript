package statement;

public class SetExpression extends Expression{
	
	private String name;
	private Expression value;

	public SetExpression(String name, Expression value) {
		super(value.getType());
		this.value = value;
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
	
	@Override
	public void typeCheck(Context context) {
		// TODO Set typechecking
		value.typeCheck(context);
	}

}
