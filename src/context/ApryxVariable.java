package context;

import statement.Expression;

public class ApryxVariable implements TypeCheckable{
	
	private String name;
	private Expression defaultValue;
	private boolean invisible;
	private Type type;
	
	public ApryxVariable(String name, Type type){
		this(name,type,null);
	}
	
	public ApryxVariable(String name, Type type, Expression defaultValue){
		this.name = name;
		this.defaultValue = defaultValue;
		this.type = type;
	}
	
	public Expression getDefaultValue() {
		return defaultValue;
	}
	
	public boolean isInvisible() {
		return invisible;
	}
	
	public void setInvisible(boolean invisible) {
		this.invisible = invisible;
	}
	
	public String getName() {
		return name;
	}
	
	public boolean hasDefaultValue(){
		return this.defaultValue != null;
	}
	
	public Type getType() {
		return type;
	}

	@Override
	public void checkType(Context context) {
		//TODO do stuff with this
	}
}
