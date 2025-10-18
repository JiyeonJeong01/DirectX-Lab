#pragma once

class CObject;

class CComponent
{
public:
    CComponent() = default;
    virtual ~CComponent() = default;

public:
    virtual void BeginPlay()	 PURE;
    virtual void TickComponent() PURE;
    virtual void Release()		 PURE;

public:
    void	 Set_Owner(CObject* _Owner) { m_Owner = _Owner; }
    CObject* Get_Owner() { return m_Owner; }

protected:
    CObject* m_Owner = nullptr;
};

