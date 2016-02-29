package ast;

public class BuiltInType extends Type{

	protected BuiltInType(String name) {
		super(name);
	}
	
	@Override
	public boolean isInvokeable() {
		return false;
	}

	@Override
	public ApryxClass getApryxClass() {
		return null;
	}

}
